#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/io.h>


#define LED_OFF _IO('z',0)
#define LED_ON  _IO('z',1)
 

// 查看芯片手册，找到 GPIO 相关寄存器物理地址
#define BASE_ADDR 0X11000000
#define GPX2CON (BASE_ADDR+0xc40) //GPX2这组 配置
#define GPX2DAT (BASE_ADDR+0xc44) //GPX2这组 数据

typedef struct MyDev
{
  struct cdev _cdev;
  dev_t devno;

  volatile void * gpx2con;//映射后的 寄存器虚拟地址
  volatile void * gpx2dat;//映射后的 寄存器虚拟地址
}MyDev;

static struct MyDev mydev;



static void led_setup(struct MyDev* dev){
    // CPX2_7 :GPX2CON[31:28]
    // CPX2_6 :GPX2CON[27:24]
    // ....
    // CPX2_1 :GPX2CON[7:4]
    // CPX2_0 :GPX2CON[3:0]
    unsigned int *p=dev->gpx2con;
    
    int input_mode=(0x01 << 28);
    unsigned int oldvalue = *p& (0x00ffffff);
    *p = oldvalue | input_mode;
}

static void led_turn_on(struct MyDev* dev){
    unsigned char *p=dev->gpx2dat;
    *p|=(1<<7);
}
static void led_turn_off(struct MyDev* dev){
    unsigned char *p=dev->gpx2dat;
    *p&=0x7f;
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
      mydev.gpx2con=ioremap(GPX2CON, 4);
      mydev.gpx2dat=ioremap(GPX2DAT,4);
      led_setup(&mydev);

      return 0;
}

static void __exit my_myled_exit(void){
        cdev_del(&mydev._cdev);
        unregister_chrdev_region(&mydev.devno, 1);
        printk("unregister_chrdev_region\n"); 
        
        if( mydev.gpx2con){
            iounmap(mydev.gpx2con);
        }
        if( mydev.gpx2dat){
            iounmap(mydev.gpx2dat);
        }
}

MODULE_LICENSE("GPL");
module_init(my_myled_init);
module_exit(my_myled_exit);