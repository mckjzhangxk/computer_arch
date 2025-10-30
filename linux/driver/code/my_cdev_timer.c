#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/timer.h>

typedef struct MyDev
{
  struct cdev _cdev;

  unsigned int second;
  struct timer_list timer;
}MyDev;
struct MyDev mydev;

void timer_fn(struct timer_list * d){
  mydev.second+=1;
  mod_timer(&mydev.timer,  jiffies + HZ);
}

int my_open_cdev (struct inode * inode, struct file * file){
    //container_of 是已知成员变量地址，求结构体地址的 宏
    // file->private_data=inode->i_cdev- &((struct Mydev*)0 )->_cdev
    file->private_data=(void*) container_of(inode->i_cdev,struct MyDev,_cdev);

    // inode->i_cdev是cdev_add传入的地址，  也就是MyDev 成员_cdev的地址
    MyDev* obj=(struct MyDev *)file->private_data;

    obj->timer.expires= jiffies + HZ;
    obj->timer.function=timer_fn;
    obj->second=0;

    add_timer(&obj->timer);
    return 0;
}
 int my_release_cdev (struct inode * inode, struct file *file){
    MyDev* obj=(struct MyDev *)file->private_data;

    del_timer(&obj->timer);
    return 0;
 }
 ssize_t my_read_cdev (struct file * file, char *user_addr, size_t n, loff_t * off){
    MyDev* obj=(struct MyDev *)file->private_data;
    int r=copy_to_user(user_addr, &obj->second,sizeof(obj->second));
    if (r)
    {
      return -1;
    }
    return sizeof(obj->second);
 }
 



struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
  .read=my_read_cdev,
};


dev_t devno;

// 编译后的操作：
// 1.sudo insmod ./my_cdev_timer.ko
// 2.cat /proc/devices |grep mycdev ,看到设备号是237
// 3.mknod /dev/myrw c 237 251
// chmod 777 /dev/myrw
// 4../open_timer
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


      // init_timer(&mydev.timer);

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