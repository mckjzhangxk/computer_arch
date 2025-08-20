#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/uaccess.h>

char BUF[1024];
int LEN=0;

int my_open_cdev (struct inode * inode, struct file * file){
    printk("my_open_cdev\n");
    return 0;
}
 int my_release_cdev (struct inode * inode, struct file *file){
  printk("my_release_cdev\n");
  return 0;
 }
 ssize_t my_read_cdev (struct file * file, char *user_addr, size_t n, loff_t * off){
  int r=copy_to_user(user_addr, BUF,LEN);// dst src n
  if (r)
  {
    return -1;
  }

  return LEN;
 }
 ssize_t my_write_cdev (struct file *file, const char *user_addr, size_t n, loff_t * off){
  LEN=n;
  int r=copy_from_user(BUF,user_addr ,n);// dst src n
  if (r)
  {
    return -1;
  }
  
  return n;
 }
dev_t devno;
struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
  .read=my_read_cdev,
  .write=my_write_cdev,
};

struct cdev _cdev;
// 编译后的操作：
// 1.sudo insmod ./my_cdev.ko
// 2.cat /proc/devices |grep mycdev ,看到设备号是237
// 3.mknod /dev/myrw c 237 251
// chmod 777 /dev/myrw
// 4../open_read_dev
int __init my_cdev_rw_init(void){
       //1.自动注册设备号
       //   参数：
	     // 251：自己指定的次设备号
	     // 1：申请的设备数量
	     // zxk：/proc/devices文件中与该设备对应的名字，方便用户层查询主设备号
       int r= alloc_chrdev_region(&devno,251,1, "mycdev");

       int major = MAJOR(devno);//主设备号
       int minor = MINOR(devno);//次设备号

       printk("register_chrdev_region %d,major:%d,minor%d\n",r,major,minor);
       //cat /proc/devices|grep mycdev

      //2.创建设备
      cdev_init(&_cdev, &ops);
      _cdev.owner=THIS_MODULE;
      r=cdev_add(&_cdev,devno, 1);
      printk("cdev_add %d\n",r);
      return 0;
}

void __exit my_cdev_rw_exit(void){
        cdev_del(&_cdev);
        unregister_chrdev_region(devno, 1);
        printk("unregister_chrdev_region\n");   
}

MODULE_LICENSE("GPL");
module_init(my_cdev_rw_init);
module_exit(my_cdev_rw_exit);