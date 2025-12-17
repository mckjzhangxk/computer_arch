#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <asm/io.h>

typedef struct MyDev
{
  struct cdev _cdev;
} MyDev;
unsigned long short_base = 0x378;
#define SHORT_NR_PORTS 8 /* use 8 ports by default */

int my_open_cdev(struct inode *inode, struct file *file)
{
  // container_of 是已知成员变量地址，求结构体地址的 宏
  //  file->private_data=inode->i_cdev- &((struct Mydev*)0 )->_cdev
  file->private_data = (void *)container_of(inode->i_cdev, struct MyDev, _cdev);

  // inode->i_cdev是cdev_add传入的地址，  也就是MyDev 成员_cdev的地址
  return 0;
}
int my_release_cdev(struct inode *inode, struct file *file)
{
  return 0;
}
ssize_t my_read_cdev(struct file *file, char *buf, size_t n, loff_t *off)
{
  MyDev *obj = (struct MyDev *)file->private_data;

  unsigned char *kbuf = kmalloc(n, GFP_KERNEL), *ptr;
  if (!kbuf)
    return -ENOMEM;
  ptr = kbuf;

  // insb(port, ptr, count);
  // rmb();

  int retval = n;
  unsigned long port = short_base;

  while (n--)
  {
    *(ptr++) = inb(port);
    rmb();
  }

  if (copy_to_user(buf, kbuf, retval)) // 写会用户空间
    retval = -EFAULT;
  kfree(kbuf);

  return retval;
}

ssize_t my_write_cdev(struct file *file, const char *buf, size_t n, loff_t *off)
{
  MyDev *obj = (struct MyDev *)file->private_data;

  unsigned char *kbuf = kmalloc(n, GFP_KERNEL), *ptr;

  if (!kbuf)
    return -ENOMEM;
  ptr = kbuf;
  if (copy_from_user(kbuf, buf, n))
    return -EFAULT;

  unsigned long port = short_base;
  int retval = n;
  while (n--)
  {
    outb(*(ptr++), port); // 端口操作：最普通的方式 outb
    wmb();
  }

  // outsb(port, ptr, count);//端口操作：使用 流操作 IO
  // wmb();
  kfree(kbuf);
  return retval;
}

struct file_operations ops = {
    .owner = THIS_MODULE,
    .open = my_open_cdev,
    .release = my_release_cdev,
    .read = my_read_cdev,
    .write = my_write_cdev,
};

struct MyDev mydev;
dev_t devno;

// 编译后的操作：
// 1.sudo insmod ./my_cdev_parallel.ko
// 2.cat /proc/devices |grep mydev ,看到设备号是237
// 3.mknod /dev/myparallel c 237 0
// chmod 777 /dev/myparallel
// 4../open_dev_read_write
// 5.1: ccat /proc/ioports |grep my_parallel可以查看申请的端口
// 5.2：qemu 模拟加入 -parallel telnet:127.0.0.1:1234,server,nowait
int __init my_cdev_rw_init(void)
{
  // 1.自动注册设备号
  //    参数：
  //  251：自己指定的次设备号
  //  1：申请的设备数量
  //  zxk：/proc/devices文件中与该设备对应的名字，方便用户层查询主设备号
  int r = alloc_chrdev_region(&devno, 0, 1, "mycdev");

  int major = MAJOR(devno); // 主设备号
  int minor = MINOR(devno); // 次设备号

  printk("register_chrdev_region %d,major:%d,minor%d\n", r, major, minor);
  // cat /proc/devices|grep mycdev

  // 2.创建设备
  cdev_init(&mydev._cdev, &ops);
  mydev._cdev.owner = THIS_MODULE;
  r = cdev_add(&mydev._cdev, devno, 1);
  printk("cdev_add %d\n", r);

  // 3.申请端口资源
  if (!request_region(short_base, SHORT_NR_PORTS, "my_parallel"))
  {
    printk(KERN_ERR "my_parallel: cannot reserve I/O port 0x%lx\n",
           short_base);
    cdev_del(&mydev._cdev);
    unregister_chrdev_region(devno, 1);
    return -EBUSY;
  }
  return 0;
}

void __exit my_cdev_rw_exit(void)
{
  cdev_del(&mydev._cdev);
  unregister_chrdev_region(devno, 1);
  release_region(short_base, SHORT_NR_PORTS);
  printk("unregister_chrdev_region\n");
}

MODULE_LICENSE("GPL");
module_init(my_cdev_rw_init);
module_exit(my_cdev_rw_exit);