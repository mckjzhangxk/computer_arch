#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/of_gpio.h>


#define LED_OFF _IO('z',0)
#define LED_ON  _IO('z',1)
 

typedef struct MyDev
{
  struct cdev _cdev;
  dev_t devno;
  int gpx2;
}MyDev;

static struct MyDev mydev;

// fs4412-leds {
// 	compatible = "fs4412,led2-5";
// 	led2-gpio = <&gpx2 7 0>;
// };

static int led_setup(struct MyDev* dev){
  struct device_node *dtr= of_find_node_by_path("/fs4412-leds");
  if(!dtr)
    return -1;
  dev->gpx2=of_get_named_gpio(dtr, "led2-gpio", 0);
  gpio_request(dev->gpx2,"led2");

  gpio_direction_output(dev->gpx2,0);
  return  0;
}

static void led_turn_on(struct MyDev* dev){
    gpio_set_value(dev->gpx2,1);
}

static void led_turn_off(struct MyDev* dev){
    gpio_set_value(dev->gpx2,0);
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
 
static long my_ioctl_cdev (struct file *file, unsigned int cmd, unsigned long arg){
   MyDev* obj=(MyDev *)file->private_data;

   // type ,nr,size,dir

    int type=_IOC_TYPE(cmd);
    if(type != 'z'){
      return -1;
    }

    int nr=_IOC_NR(cmd);
    switch (nr)
    {
    case 0:
       led_turn_off(obj);
      break;
    case 1:
      led_turn_on(obj);
      break;
    default:
      return -1;
      break;
    }
    return 0;
  }

struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
  .unlocked_ioctl=my_ioctl_cdev,
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
       int r= alloc_chrdev_region(&mydev.devno,0,1, "myled");
          
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
      if(led_setup(&mydev)<0){
        printk("led_setup Error\n");
      }

      return 0;
}

static void __exit my_myled_exit(void){
        cdev_del(&mydev._cdev);
        unregister_chrdev_region(&mydev.devno, 1);
        printk("unregister_chrdev_region\n"); 
  
        gpio_free(mydev.gpx2);
}

MODULE_LICENSE("GPL");
module_init(my_myled_init);
module_exit(my_myled_exit);