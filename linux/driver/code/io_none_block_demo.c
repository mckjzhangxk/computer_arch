#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/uaccess.h>

#define MAX_SIZE 1024
typedef struct MyDev
{
  struct cdev _cdev;
  char BUF[MAX_SIZE];
  int head;
  int tail;
}MyDev;

/////////////////环形队列的方法/////////////////////////////////


static int isEmply(MyDev* obj){
  return obj->head==obj->tail;
}

static int isFull(MyDev* obj){
  return (obj->head+1)%MAX_SIZE==obj->tail;
}
static int size(MyDev* obj){
  int sz=obj->head-obj->tail;
  if (sz<0)
    sz+=MAX_SIZE;
  return sz;
}
static int avail(MyDev* obj){
  return MAX_SIZE-1 -size(obj);
}

static void writedata(MyDev* obj, char* src, int n){
  
  int i;
  for ( i = 0; i < n; i++){
       obj->BUF[obj->head]=src[i];
       obj->head=(obj->head+1)%MAX_SIZE;
  }
}

static void readdate(MyDev* obj, char* dst, int n){
      int i;
      for ( i = 0; i < n; i++)
      {
        dst[i]=obj->BUF[obj->tail];
        obj->tail=(obj->tail+1)%MAX_SIZE;
      }
}

//////////////////////////////////////////////////


static int  my_open_cdev (struct inode * inode, struct file * file){
    //container_of 是已知成员变量地址，求结构体地址的 宏
    // file->private_data=inode->i_cdev- &((struct Mydev*)0 )->_cdev
    file->private_data=(void*) container_of(inode->i_cdev,struct MyDev,_cdev);

    // inode->i_cdev是cdev_add传入的地址，  也就是MyDev 成员_cdev的地址
    return 0;
}
 static int my_release_cdev (struct inode * inode, struct file *file){
  return 0;
 }
 static ssize_t my_read_cdev (struct file * file, char *user_addr, size_t n, loff_t * off){
   MyDev* obj=(struct MyDev *)file->private_data;

   if(isEmply(obj)){//empty
      return -2;
   }
   
    int sz=size(obj);

    int m=n<sz?n:sz;
    char tmp[m];
    readdate(obj,tmp,m);
    

      int r=copy_to_user(user_addr, tmp,m);
      if (r){
        return -1;
      }
      return m;
 }
 static ssize_t my_write_cdev (struct file *file, const char *user_addr, size_t n, loff_t * off){
   MyDev* obj=(struct MyDev *)file->private_data;

   if(isFull(obj)){//full
        return -2;
   }
   int sz=avail(obj);

   
   int m=n<sz?n:sz;
   char tmp[m];
   int r=copy_from_user(tmp,user_addr ,m);
   if (r)
     return -1;
  writedata(obj,tmp,m);

  
  return m;
 }


struct file_operations ops={
  .owner=THIS_MODULE,
  .open=my_open_cdev,
  .release=my_release_cdev,
  .read=my_read_cdev,
  .write=my_write_cdev,
};

struct MyDev mydev;
dev_t devno;

// 编译后的操作：
// 1.sudo insmod ./my_cdev.ko
// 2.cat /proc/devices |grep mydev ,看到设备号是237
// 3.mknod /dev/myrw c 237 251
// chmod 777 /dev/myrw
// 4.1 echo "hello world"> /dev/myrw 
// 4.2 cat /dev/myrw 
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

      mydev.head=mydev.tail=0;
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