#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/uaccess.h>


static int err_code;

typedef struct MyDev
{
  struct cdev _cdev;
}MyDev;
static struct MyDev mydev;

int my_open_cdev (struct inode * inode, struct file * file){
    return 0;
}
 int my_release_cdev (struct inode * inode, struct file *file){
  return 0;
 }
 ssize_t my_read_cdev (struct file * file, char *user_addr, size_t n, loff_t * off){
    return -err_code;
 }
 ssize_t my_write_cdev (struct file *file, const char *user_addr, size_t n, loff_t * off){  
  return 0;
 }

  long my_ioctl_cdev (struct file *file, unsigned int cmd, unsigned long arg){
    err_code=arg;
    printk(KERN_ALERT "Get Error Colde %d\n",err_code);
    return 0;
  }

struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
  .read=my_read_cdev,
  .write=my_write_cdev,
  .unlocked_ioctl=my_ioctl_cdev
};


static dev_t devno;
// 本程序演示的是 设备层返回 -code 与 app层 errno 的对应关系

// 编译后的操作：
// 1.sudo insmod ./my_error_dev.ko
// 2.cat /proc/devices |grep mydev ,看到设备号是236
// 3.sudo  mknod -m 666 /dev/myerror c 236 0
// 4../error_code_test /dev/myerror
int __init my_cdev_rw_init(void){
       //1.自动注册设备号
       //   参数：
	     // 251：自己指定的次设备号
	     // 1：申请的设备数量
	     // zxk：/proc/devices文件中与该设备对应的名字，方便用户层查询主设备号
       int r= alloc_chrdev_region(&devno,0,1, "mycdev");

       int major = MAJOR(devno);//主设备号
       int minor = MINOR(devno);//次设备号

       printk(KERN_ALERT "register_chrdev_region %d,major:%d,mino:%d\n",r,major,minor);
       //cat /proc/devices|grep mycdev

             //2.创建设备
      cdev_init(&mydev._cdev, &ops);
      mydev._cdev.owner=THIS_MODULE;
      r=cdev_add(&mydev._cdev,devno, 1);
      printk("cdev_add %d\n",r);

      return 0;
}

void __exit my_cdev_rw_exit(void){
        cdev_del(&mydev._cdev);
        unregister_chrdev_region(devno, 1);
        printk(KERN_ALERT "unregister_chrdev_region\n");   
}

MODULE_LICENSE("GPL");
module_init(my_cdev_rw_init);
module_exit(my_cdev_rw_exit);
