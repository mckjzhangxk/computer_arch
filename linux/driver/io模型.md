## 5种IO模型
- 阻塞
- 非阻塞
![alt text](img/非阻塞.jpg)
- 多路复用
- 信号:收到信号后读
- 异步IO(DMA):收到信号后读完成


## 阻塞

- 就系队列：runnable 的进程，可以被scheduler调度。
- 等待队列：资源不满足的情况下把进程插入到此队列，此队列的进程不会被scheduler调度，进程是sleep态。
- 等待队列分为2中，可被信号中断的 和不可 被信号中断的
- 一旦满足再次被调用条件，需要wakeup 等待队列
- [block_demo.c](data/block_demo.c)
```c
// 应用层设置 阻塞与非阻塞
void set_fd_noblock(int fd) {
    int flag = fcntl(fd, F_GETFD);
    fcntl(fd, F_SETFD, flag | O_NONBLOCK);
}
void set_fd_block(int fd) {
    int flag = fcntl(fd, F_GETFD);
    fcntl(fd, F_SETFD, flag & (~O_NONBLOCK) );
}
```

```c
// 驱动层等待队列 
wait_queue_head_t wq//等待队列头数据类型
init_waitqueue_head(wait_queue_head_t *pwq) //初始化等待队列头
    
// 睡眠
wait_event_interruptible(wq,condition)
/*
功能：条件不成立则让任务进入浅度睡眠，直到条件成立醒来
    wq:等待队列头
    condition：C语言表达式
返回：正常唤醒返回0，信号唤醒返回非0（此时读写操作函数应返回-ERESTARTSYS）
*/
        
wait_event(wq,condition) //深度睡眠


// 唤醒
wake_up_interruptible(wait_queue_head_t *pwq)  
wake_up(wait_queue_head_t *pwq)

```

## 多路复用
- select,poll,epoll三种实现
- - select: 描述符数量受限，效率低
- - poll: 链表实现，数量不受限，效率低
- - epoll: 数量不受限，效率高
- 见[poll_demo.c](data/poll_demo.c)

## 信号驱动
- 见 [signal_demo.c](data/signal_demo.c)