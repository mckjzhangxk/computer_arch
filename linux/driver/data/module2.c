   #include <linux/module.h>
   #include <linux/kernel.h>

    extern int g_int;


   int __init module2_init(void)
   {
    printk("module2_init g_int=%d\n",g_int);
        return 0;
   }

   void __exit module2_exit(void)
   {
        printk("module2_exit will exit\n");
   }


   MODULE_LICENSE("GPL");
   module_init(module2_init);
   module_exit(module2_exit);