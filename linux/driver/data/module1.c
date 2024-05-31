   #include <linux/module.h>
   #include <linux/kernel.h>

    int g_int=2;


   int __init module1_init(void)
   {
    printk("module1_init g_int=%d\n",g_int);
        return 0;
   }

   void __exit module1_exit(void)
   {
        printk("module1_exit will exit\n");
   }


   MODULE_LICENSE("GPL");
   module_init(module1_init);
   module_exit(module1_exit);


   EXPORT_SYMBOL(g_int);