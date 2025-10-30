
   #include <linux/module.h>
   #include <linux/kernel.h>
   #include <linux/rbtree.h>


    struct mypage {
        int offset;
        struct rb_node rb_node;
    };
    
    static struct mypage* search(struct rb_root* rb,int offset){

        struct rb_node* n=rb->rb_node;

        while (n)
        {
            struct mypage* p=rb_entry(n,struct mypage,rb_node);
            if (offset<p->offset)
                n=n->rb_left;
            
            else if (offset>p->offset)
                n=n->rb_right;
            else
                return p;
        }
        return NULL;
    }
    
    static void insert(struct rb_root* root,struct mypage* data)
    {
        struct rb_node** new=&root->rb_node; //new 地址存放 一个 rb_node* 指针
        struct rb_node* parent=NULL;

        int offset=data->offset;

        while (*new)
        {
            
            parent=*new;
            struct mypage* p=rb_entry(parent,struct mypage,rb_node);


            if(p->offset < offset)
                new=&(*new)->rb_left;
            else if (p->offset > offset)
                new=&(*new)->rb_right;
            else
                return;
        }

        rb_link_node(&data->rb_node,parent,new);//执行 *new = &data->rb_node;
        rb_insert_color(&data->rb_node,root);// 调整颜色
        
    };
    
   int __init rbtree_init(void)
   {
	   
    struct rb_root root = RB_ROOT; 

    int i;
    struct mypage pgs[3]={0};

    for ( i = 0; i < 3; i++)
    {
        pgs[i].offset=(i+1)*10;
        insert(&root,&pgs[i]);
    }
    
    

     struct mypage* p=search(&root,10);
     if(p)
   	    printk("find page offset=%d\n",p);
     else
        printk("not found\n");
     return 0;
   }


   void __exit rbtree_exit(void)
   {
   
   }
   MODULE_LICENSE("GPL");
   
module_init(rbtree_init);
module_exit(rbtree_exit);



MODULE_AUTHOR("zhangxiaokai");
MODULE_DESCRIPTION("my program");
MODULE_ALIAS("myzxk");
