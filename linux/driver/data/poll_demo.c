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

  
  char BUF[MAX_SIZE];//最大容量应该是MAX_SIZE-1
  int head;//下一个写的位置
  int tail;//下一个读取的位置
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
 ssize_t my_read_cdev (struct file * file, char *user_addr, size_t n, loff_t * off){
   MyDev* obj=(struct MyDev *)file->private_data;

   if(obj->head==obj->tail){//队列为空
      if(file->f_flags&O_NONBLOCK)//非阻塞模式
        return -2;
      
      //阻塞：直到条件满足
      int ret=wait_event_interruptible(obj->rq,obj->head!=obj->tail);//或者 wait_event(wq,condition) //深度睡眠
      if (ret)//信号被中断
      {
        return -ERESTART;
      }
      
   }
   
    int sz=obj->head-obj->tail;//对多可以读取的字节数量
    if (sz<0)
      sz+=MAX_SIZE;

      int m=n<sz?n:sz;//实际 需要读取的字节数量
      char tmp[m];
      int p=0,cnt=m;

      //读取m个字节到tmp中
      int i;
      for ( i = 0; i < cnt; i++)
      {
       tmp[p++]=obj->BUF[obj->tail];
        obj->tail=(obj->tail+1)%MAX_SIZE;
      }
      //复制回用户空间
      int r=copy_to_user(user_addr, tmp,m);
      if (r){
        return -1;
      }
      //通知 有空间去写了
      wake_up_interruptible(&obj->wq);
      return m;
 }
 ssize_t my_write_cdev (struct file *file, const char *user_addr, size_t n, loff_t * off){
   MyDev* obj=(struct MyDev *)file->private_data;

   if( (obj->head+1)%MAX_SIZE==obj->tail){//缓冲区满了
      if(file->f_flags&O_NONBLOCK)//非阻塞模式
          return -1;
      
      //阻塞：直到 条件满足
      int ret=wait_event_interruptible(obj->wq, (obj->head+1)%MAX_SIZE!=obj->tail  );//或者 wait_event(wq,condition) //深度睡眠
      if (ret)//信号被中断
      {
        return -ERESTART;
      }
   }
   
   int avil=obj->tail-obj->head-1;//剩余写的空间
   if (avil<0)
      avil+=MAX_SIZE;
   
   int m=n<avil?n:avil;//实际写的空间
   char tmp[m];
   int r=copy_from_user(tmp,user_addr ,m);//临时写入到tmp中
   if (r)
     return -1;
    //tmp复制回obj->BUF中
    int i;
    for ( i = 0; i < m; i++){
       obj->BUF[obj->head]=tmp[i];
       obj->head=(obj->head+1)%MAX_SIZE;
    }
  //唤醒读队列，因为已经写了数据，可以读取了
  wake_up_interruptible(&obj->rq);
  return m;
 }
//本函数的作用
// 1.设置 阻塞队列
// 2.返回设备 是否可读/可写
__poll_t my_poll_cdev (struct file *file, struct poll_table_struct *ptb){
  MyDev* obj=(struct MyDev *)file->private_data;
  __poll_t mask=0;
  //加入队列 到 poll_table中
  poll_wait(file, &obj->rq, ptb);
  poll_wait(file, &obj->wq, ptb);

  if (obj->head!=obj->tail)//不空可读
  {
    mask |= POLLIN | POLLRDNORM;
  }
  
  if ((obj->head+1)%MAX_SIZE!=obj->tail)//不满 可写
  {
    mask |= POLLOUT | POLLWRNORM;
  }
  
  return mask;
}
struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
  .read=my_read_cdev,
  .write=my_write_cdev,
  .poll=my_poll_cdev,
};

struct MyDev mydev;
dev_t devno;

// 编译后的操作：
// 1.sudo insmod ./my_cdev.ko
// 2.cat /proc/devices |grep mydev ,看到设备号是237
// 3.mknod /dev/myrw c 237 251
// chmod 777 /dev/myrw
// 4.1 ./open_select
// 4.2 echo xxx> /dev/myrw 
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
      mydev.head=mydev.tail=0;
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