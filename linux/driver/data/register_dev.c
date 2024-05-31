   #include <linux/module.h>
   #include <linux/kernel.h>
   #include <linux/fs.h>


  dev_t devno;

   int __init my_register_init(void)
   {

     //    int major = 251;//主设备号
     //    int minor = 2;//次设备号
     //    devno = MKDEV(major,minor);

     //    int r=register_chrdev_region(devno, 1, "mydevice");

       //自动生成一个设备号,主设备号由内核生成  
     //   参数：
	// 251：自己指定的次设备号
	// 1：申请的设备数量
	// zxk：/proc/devices文件中与该设备对应的名字，方便用户层查询主设备号
       int r= alloc_chrdev_region(&devno,251,1, "zxk");

        int major = MAJOR(devno);//主设备号
        int minor = MINOR(devno);//次设备号

        printk("register_chrdev_region %d,major:%d,minor%d\n",r,major,minor);
          //cat /proc/devices|grep zxk
        return 0;
   }

   void __exit my_register_exit(void)
   {
        unregister_chrdev_region(devno, 1);
        printk("unregister_chrdev_region\n");
   }

   MODULE_LICENSE("GPL");
   module_init(my_register_init);
   module_exit(my_register_exit);