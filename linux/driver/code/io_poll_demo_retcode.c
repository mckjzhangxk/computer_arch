#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/poll.h>
#define MAX_SIZE 1024
typedef struct MyDev
{
  struct cdev _cdev;
  __poll_t retCode;
  wait_queue_head_t rq;
  wait_queue_head_t wq;
}MyDev;



int my_open_cdev (struct inode * inode, struct file * file){
    //container_of 是已知成员变量地址，求结构体地址的 宏
    // file->private_data=inode->i_cdev- &((struct Mydev*)0 )->_cdev
    file->private_data=(void*) container_of(inode->i_cdev,struct MyDev,_cdev);

    // inode->i_cdev是cdev_add传入的地址，  也就是MyDev 成员_cdev的地址
    return 0;
}
 int my_release_cdev (struct inode * inode, struct file *file){
  return 0;
 }

 
 ssize_t my_write_cdev (struct file *file, const char *user_addr, size_t n, loff_t * off){
   MyDev* obj=(struct MyDev *)file->private_data;

  
   char tmp;
   int r=copy_from_user(&tmp,user_addr ,1);//临时写入到tmp中
   printk(KERN_ALERT "get cmd %c,n=%d\n",tmp,n);
   switch (tmp)
   {
   case '0':
      obj->retCode=POLLIN | POLLWRNORM;
      wake_up_interruptible(&obj->rq);
      break;
   case '1':
      obj->retCode=POLLOUT | POLLWRNORM;
      wake_up_interruptible(&obj->wq);
      break;  
   case '2':
      obj->retCode=POLLHUP;
      wake_up_interruptible(&obj->rq);
      break;  
   case '3':
      obj->retCode=POLLERR;
      wake_up_interruptible(&obj->rq);
      wake_up_interruptible(&obj->wq);
      break;  
   default:
    break;
   }
  //唤醒读队列，因为已经写了数据，可以读取了
  return n;
 }
//本函数的作用

// 1.ptb 是 poll_wait 函数的真正实现(select,poll,epoll)
// 2.如果 ptb 不是 null, 则current 进程 加入到了 对应的 等待队列中
// 3.返回值 mask 告诉内核，当前设备的状态，如果 mask!=0, 上层的 select,poll不会 sleep
__poll_t my_poll_cdev (struct file *file, struct poll_table_struct *ptb){
  MyDev* obj=(struct MyDev *)file->private_data;
  __poll_t mask=obj->retCode;
  
  // 这一行是 产生busy loop 的原因，  如果不清理，永远都会执行
  obj->retCode=0;


  // 调用  ptb->qproc(file, &obj->rq, ptb);
  poll_wait(file, &obj->rq, ptb);
  poll_wait(file, &obj->wq, ptb);

  printk(KERN_ALERT "poll call,%d",mask);
  return mask;
}
struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
  .write=my_write_cdev,
  .poll=my_poll_cdev,
};

struct MyDev mydev;
dev_t devno;

// 编译后的操作：
// 1.sudo insmod ./io_poll_demo_retcode.ko
// 2.cat /proc/devices |grep mycdev ,看到设备号是237
// 3.mknod /dev/myrw c 237 251
// chmod 777 /dev/myrw
// 4.1: ./app_iopoll_retcode /dev/myrw 观察控制台打印
// 4.2 echo -n '0'> /dev/myrw 
//  0->表示有数据可读
//  1->数据可写
//  2->HUP
//  3->ERR
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

      //初始化队列
      init_waitqueue_head(&mydev.rq);
      init_waitqueue_head(&mydev.wq);

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