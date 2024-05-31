   #include <linux/module.h>
   #include <linux/kernel.h>
   
    int g_int=2;
    char * g_str="hello";
    int g_array[3]={1,2,3};


    module_param(g_int,int,0644);
    module_param(g_str,charp,0644);
    module_param_array(g_array,int,NULL,0644);

   int __init my_init(void)
   {
    int i;
    printk("g_int=%d\n",g_int);
    printk("g_str=%s\n",g_str);

    for ( i = 0; i < 3; i++)
    {
        printk("g_array[%d]=%d\n",i,g_array[i]);
    }

        return 0;
   }

   void __exit my_exit(void)
   {
        printk("myhello will exit\n");
   }

   MODULE_LICENSE("GPL");
   module_init(my_init);
   module_exit(my_exit);