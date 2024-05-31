
   #include <linux/module.h>
   #include <linux/kernel.h>
   
   //__init宏，展开后为：__attribute__ ((__section__ (".init.text")))
   //指示链接器将该函数放置在 .init.text区段
   //在模块插入时方便内核从ko文件指定位置读取入口函数的指令到特定内存位置
   int __init myhello_init(void)
   {
   	printk("#####################################################\n");
   	printk("#####################################################\n");
   	printk("#####################################################\n");
   	printk("#####################################################\n");
       printk("myhello is running\n");
   	printk("#####################################################\n");
   	printk("#####################################################\n");
   	printk("#####################################################\n");
   	printk("#####################################################\n");
   	return 0;
   }
   //__exit展开后为：__attribute__ ((__section__ (".exit.text")))
   //指示链接器将该函数放置在 .exit.text区段
   void __exit myhello_exit(void)
   {
   	printk("myhello will exit\n");
   }
   //字符串常量内容为源码的许可证协议 可以是"GPL" "GPL v2"  "GPL and additional rights"  "Dual BSD/GPL"  "Dual MIT/GPL" "Dual MPL/GPL"等, "GPL"最常用
   MODULE_LICENSE("GPL");
   //module_init 宏
   //静态加载时：本质是定义一个全局函数指针,赋值myhello_init,方便系统初始化统一调用。
   //动态加载时：由于内核模块的默认入口函数名是init_module,用该宏可以给对应模块入口函数起别名myhello_init
   module_init(myhello_init);

   //动态加载: 模块在卸载时，对应函数被调用
   //静态加载: 实际上对应函数被忽略
   module_exit(myhello_exit);



MODULE_AUTHOR("zhangxiaokai");
MODULE_DESCRIPTION("my program");
MODULE_ALIAS("myzxk");