## 文件系统的数据结构
![layers.png](imgs%2Flayers.png)

- Disk的基本单元是sector(block),一般512k
- xv6的block由2个Disk.sector组成
- Supter block中存放的是 
- - 1.#total block
- - 2.#data block
- - 3.#logging block
- - 4.#inode
- - 5.log,inode,bitmap的起始位置
- Inode对应文件或者文件夹，由一个inode number标识。

## xv6的基本结构
| 名称                    | 数值                              |
|-----------------------|---------------------------------|
| Block Size            | 1024 bytes                      |
| total Size            | 2000 blocks,2MB                 |
| logging start         | 2                               |
| logging size          | 30 blocks                       |
| inode position        | 32                              |
| inode size            | 13 blocks                       |
| Inodes Per Block(IPB) | (1024/64)=16,struct inode 64个字节 |
| 最大支持的文件数量             | 13*16=208个                      |
| 最大文件                  | 12+(1024/4)=268 block,268KB     |
| bmp position          | 45                              |
| bmp size              | 1 block,管理8*1024=8192个block,8MB |


## 问题
- fs.img是什么作用
- - 由mkfs程序产生，保存的是整个文件系统的内容。
- - 包括boot,super,inodes,bitmap,data
- - data中保存 Dir ,ls, cat ...
- - inodes保存文件的root,和其他的文件信息。

- buffer cache怎么回事？
- - <font color=red>本质就是 磁盘的block读取到内存中，在内存中操作，最终回写回磁盘。</font>
- - 注意1：os指派的时候，一定要保证 一个disk block最多对应1个 buf cache，所以需要对[分配的结构]锁保护。
- - 注意2：一个【buf cache】 不可以被多个thread同时操作，所以需要对【buf cache锁】保护。
- - 注意6：当某个【buf cache】完成使用后，调用brelease,这样就释放掉的cache.lock,并且本cache成为了Most recent uesd cache.
- - 注意3：【buf cache】需要有 valid,disk 2个字段来保存与磁盘的同步状态，valid表示是否加载disk block,disk表示是否回写会disk
- - 注意4：os的 buffer cache 总容量远小于磁盘容量，当buffer cache不够时，需要【腾出】LRU的,来加载正被需要的disk block
- - 注意5：通过buf.refcnt记录【buf cache】被引用的次数，0的时候，表示本cache可以安全的加载其他dick block.

- inode 怎么回事？
- - inode表示文件，主要的成员是 inum,type,(dev,major,minor)，size.
- - addrs[12+1]，开始12个是block no,最后一个addr[12]指向间接表.
- - nlink,valid??
![inode.png](imgs%2Finode.png)
- 文件目录是什么？
- - 特殊的inode,type=dir
- - 对应的block中存放 目录条目.

```c
struct dirent {//目录的entry
  ushort inum; //0表示没被占用的entry
  char name[DIRSIZ];
};

- echo "abc" > a.txt，这个操作具体对应哪几个步骤.
- - 1.fd=open("a.txt"),
- - - 创建一个inode:遍历super.ninodes,找出一个type=0的inode.
- - - 然后操作目录对象，追加 struct dirent到 rootinode的block中
- - 2.write(fd,"abc"),
- - - 计算出要写的inode block number,修改对应的bitmap
- - - 往 inode block number 中写入"abc".


//总而言之：创建并追加文件内容需要 三种磁盘的操作
1.为新文件创建inode,并更新inode的基本信息
2.更新新文件所在文件夹的 inode信息（包括inode的内容：目录条目）
3.对inode内容的block 的数据追加操作。
```
- 文件系统的结构是怎样的？
- - 层次划分: filedescriptor --> path -->dir -->inode -->logging --> buffer cache --> disk
- 如何执行原子操作（事务）？
- - logging:一个系统调用，可能有多个write block,如果在执行过程中有一个失败，之前执行的需要回滚。采用logging来保证事务的原子性
- - 实现原理
```shell
logwrite (b1,b2,b3)

1.把b1,b2,b3写入到log block中,eg b1->log[1],b2->log[2],b3->log[3]
2.更新log block[0],记录已经是3个block就绪,这也就是commit point
3.安装阶段，把log[1],log[2],log[3]回写会磁盘
4.把log block[0]的 计数清0，表示提交完成log

//log block[0]的存储
struct logheader {
  int n;  //n块提交
  int block[LOGSIZE];
};
```
- - <font color=pink>恢复阶段： 启动的第一个进程检查 block[0]的计数，不是0执行 上面第三，第四步骤</font>
- - 系统调用 必须是事务，多个系统调用可以合并成一个事务。
- - xv6的log blocks大小是固定，这对于同最多操作的block是有限制的
- 与驱动层的关系?virtio是什么？
- - virtio是虚拟的磁盘，属于xv6的最底层
- 软link和硬link的区别？
- - 硬link的创建 不分先后，本质是把inode的引用+1，而且并不会创建新的inode。
- - 软link不会增加old inode的引用, 可能的实现是：创建一个新文件，type设置从S,节点的内容是old 的路径地址（类似于dir的条目）
```shell
#ln old  new
ln /root/a /home/zxk/b


#对于硬link
#1./root/a 对应的inode的 nlink+1
#2.在/home/zxk这个目录下 追加条目b
#3.条目的内容的 /root/a 对应的inode 的inum num

```
- 管道pipe的实现？
