#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>

 

typedef struct MyDev
{
  struct cdev _cdev;
  dev_t devno;
  int gpx1;
  int irq;
  struct work_struct my_work;
}MyDev;

static struct MyDev mydev;


// mykey2_node {
// 	compatible = "mykey2,key2";
// 	key2-gpio = <&gpx1 1 0>;
// 	interrupt-parent = <&gpx1>;
// 	interrupts = <1 3>;
// };

static irqreturn_t my_button_irq_handler(int irq, void *dev_id){
  struct MyDev* dev=(struct MyDev*)dev_id;
  // int value=gpio_get_value(dev->gpx1);
  // printk("my_button_irq_handler: gpio:%d, value:%d\n", dev->gpx1, value);
  schedule_work(&dev->my_work);
  return IRQ_HANDLED;
}

void work_queue_func(struct work_struct  *work){
  struct MyDev* dev=container_of(work, struct MyDev, my_work);
  int value=gpio_get_value(dev->gpx1);
  printk("work_queue_func: gpio:%d, value:%d\n", dev->gpx1, value);

}
static int button_setup(struct MyDev* dev){
  struct device_node *dtr= of_find_node_by_path("/fs4412-leds");
  if(!dtr)
    return -1;
  dev->gpx1=of_get_named_gpio(dtr, "key2-gpio", 0);
  gpio_request(dev->gpx1,"button2");
  gpio_direction_input(dev->gpx1);
  
  
  int irq=irq_of_parse_and_map(dtr, 0);
  if(irq < 0){
    printk("irq_of_parse_and_map error\n");
    return -1;
  }

  // 注册中断处理函数
  int r=request_irq(irq,
                   (irq_handler_t)my_button_irq_handler,
                   0,
                   "my_button_irq",
                   (void*)dev);
  if(r < 0){
    printk("request_irq error %d\n", r);
    return -1;
  }
  dev->irq=irq;


  INIT_WORK(&dev->my_work, work_queue_func);
  printk("button_setup ok, gpio:%d, irq:%d\n", dev->gpx1, dev->irq);
  return 0;
}






static int my_open_cdev (struct inode * inode, struct file * file){
   file->private_data=(void*) container_of(inode->i_cdev,struct MyDev,_cdev);
    printk("my_open_cdev\n");
    return 0;
}
static int my_release_cdev (struct inode * inode, struct file *file){
  printk("my_release_cdev\n");
  return 0;
 }
 

 
struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
};



//
// 编译后的操作：
// 1.sudo insmod ./my_cdev.ko
// 2.cat /proc/devices |grep mycdev ,看到设备号是237
// 3.mknod /dev/mydev c 237 251
// 4../open_dev
static int __init my_myled_init(void){
       //1.自动注册设备号
       //   参数：
	     // 0：自己指定的次设备号
	     // 1：申请的设备数量
	     // zxk：/proc/devices文件中与该设备对应的名字，方便用户层查询主设备号
       int r= alloc_chrdev_region(&mydev.devno,0,1, "mybutton");
          
       int major = MAJOR(mydev.devno);//主设备号
       int minor = MINOR(mydev.devno);//次设备号

       printk("register_chrdev_region %d,major:%d,minor%d\n",r,major,minor);
       //cat /proc/devices|grep mycdev

      //2.创建设备
      cdev_init(&mydev._cdev, &ops);
      mydev._cdev.owner=THIS_MODULE;
      r=cdev_add(&mydev._cdev,mydev.devno, 1);
      printk("cdev_add %d\n",r);


      //3.IO内存映射
      if(button_setup(&mydev)<0){
        printk("led_setup Error\n");
      }

      return 0;
}

static void __exit my_myled_exit(void){
        cdev_del(&mydev._cdev);
        unregister_chrdev_region(&mydev.devno, 1);
        printk("unregister_chrdev_region\n"); 
  
        gpio_free(mydev.gpx1);

        free_irq(mydev.irq, (void*)&mydev);
}

MODULE_LICENSE("GPL");
module_init(my_myled_init);
module_exit(my_myled_exit);