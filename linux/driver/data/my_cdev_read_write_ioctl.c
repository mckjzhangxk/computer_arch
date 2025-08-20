#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/uaccess.h>

typedef struct MyDev
{
  struct cdev _cdev;
  char BUF[1024];
  int LEN;
}MyDev;


int my_open_cdev (struct inode * inode, struct file * file){
    //container_of 是已知成员变量地址，求结构体地址的 宏
    // file->private_data=inode->i_cdev- &((struct Mydev*)0 )->_cdev
    file->private_data=(void*) container_of(inode->i_cdev,struct MyDev,_cdev);
    return 0;
}
 int my_release_cdev (struct inode * inode, struct file *file){
  return 0;
 }
 ssize_t my_read_cdev (struct file * file, char *user_addr, size_t n, loff_t * off){
   MyDev* obj=(MyDev *)file->private_data;
  int r=copy_to_user(user_addr, obj->BUF,obj->LEN);
  if (r)
  {
    return -1;
  }

  return obj->LEN;
 }
 ssize_t my_write_cdev (struct file *file, const char *user_addr, size_t n, loff_t * off){
   MyDev* obj=(MyDev *)file->private_data;

   obj->LEN=n;
   int r=copy_from_user(obj->BUF,user_addr ,n);
   if (r)
   {
     return -1;
   }
  
  return n;
 }

  long my_ioctl_cdev (struct file *file, unsigned int cmd, unsigned long arg){
   MyDev* obj=(MyDev *)file->private_data;

//     /* used to decode ioctl numbers */
// #define _IOC_DIR(nr)        (((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
// #define _IOC_TYPE(nr)       (((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
// #define _IOC_NR(nr)     (((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
// #define _IOC_SIZE(nr)      (((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)
    int nr=_IOC_NR(cmd);
    switch (nr)
    {
    case 0:
      copy_to_user((int*)arg,&obj->LEN,sizeof(int));
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
  .read=my_read_cdev,
  .write=my_write_cdev,
  .unlocked_ioctl=my_ioctl_cdev
};

struct MyDev mydev;
dev_t devno;

// 编译后的操作：
// 1.sudo insmod ./my_cdev_read_write_ioctl.ko
// 2.cat /proc/devices |grep mydev ,看到设备号是236
// 3.mknod sudo mknod -m 666 /dev/myrw_ctl c 236 251
// 4../open_read_ioctl_dev
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
      cdev_init(&mydev._cdev, &ops);
      mydev._cdev.owner=THIS_MODULE;
      r=cdev_add(&mydev._cdev,devno, 1);
      printk("cdev_add %d\n",r);
      return 0;
}

void __exit my_cdev_rw_exit(void){
        cdev_del(&mydev._cdev);
        unregister_chrdev_region(devno, 1);
        printk("unregister_chrdev_region\n");   
}

MODULE_LICENSE("GPL");
module_init(my_cdev_rw_init);
module_exit(my_cdev_rw_exit);
