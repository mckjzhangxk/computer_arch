
   #include <linux/module.h>
   #include <linux/kernel.h>
   #include <linux/list.h>


    struct fox {
        int id;
        struct list_head list;
    };
    
    

   int __init mylist_init(void)
   {
	   
    LIST_HEAD(fox_list);
    
    struct fox redfox[5];
    int i; 
    for (i = 0; i < 5; i++)
    {
       struct fox* p=&redfox[i];
       p->id=i+1;
       INIT_LIST_HEAD(&p->list);

       list_add(&p->list, &fox_list);
       //list_add_tail(&p->list, &fox_list);
    }
    
    struct fox* f;
    list_for_each_entry(f,&fox_list,list){
        printk("fox %d\n",f->id);
    }

    /*list_for_each_entry_reverse(f,&fox_list,list){
        printk("fox %d\n",f->id);
    }*/
   	return 0;
   }
   void __exit mylist_exit(void)
   {
   
   }
   MODULE_LICENSE("GPL");
   
   module_init(mylist_init);
   module_exit(mylist_exit);



MODULE_AUTHOR("zhangxiaokai");
MODULE_DESCRIPTION("my program");
MODULE_ALIAS("myzxk");
