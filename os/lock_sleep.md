## spinLock
```c
struct spinlock {
  uint locked;       // Is the lock held?
};

void acquire(struct spinlock *lk){
    turnoff_interrupt();        //关中断，防止死锁
    while( test_and_set(lk->lock) ){ 
        //1.test_and_set是原子操作
        //2.test_and_set 返回 当前lk->lock
        //3.设置lk->lock=1
    }
}

void release(struct spinlock *lk){
    turnon_interrupt();
    lk->lock=0;//这里假定是原子操作
}
```

## scheduler 与sched

### scheduler
- scheduler是每个CPU都会执行的一个调用线程，用于从 scheduler线程 切换到其他进程的执行。
- CPU.Context保存这scheduler这个线程的上下文
```c
void scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();//mycpu()->context 里面保存scheduler这个线程的执行

  c->proc = 0;
  while(1){
      
    for(p = proc; p < &proc[NPROC]; p++) {
      acquire(&p->lock);
      if(p->state == RUNNABLE) {
        // Switch to chosen process.  It is the process's job
        // to release its lock and then reacquire it
        // before jumping back to us.
        p->state = RUNNING;
        c->proc = p;
        swtch(&c->context, &p->context);//切换到p->context，会release(&p->lock),
    

        //直到p被tiemer中断后，再次执行 swtch(&p->context,&c->context)，才会执行本语句 
        // 而且 会被再次 acquire(&p->lock);
        
        c->proc = 0;//sched"返回"到这里
      }
      release(&p->lock);//释放从sched获得的锁
    }
  }
}
```


### Sched
- Sched是用户进程 切换成Scheduler进行的方法
- myproc()->context会暂存 当前线程的上下文
- 用户进程实际是调用yield 进行切换的，而不是直接调用Sched
```c
void sched(void)
{
  int intena;
  struct proc *p = myproc();
  
  if(!holding(&p->lock))
    panic("sched p->lock");
  if(mycpu()->noff != 1)  //mycpu()->noff 是调用push_off的次数，也就是等价于调用accquire(lock)的次数，
    panic("sched locks"); //switch的时候，进程只可以获得一把进程锁(p->lock)，否则就 有可能 造成死锁,而无法switch back
  if(p->state == RUNNING)
    panic("sched running");
  if(intr_get())
    panic("sched interruptible");

  intena = mycpu()->intena;
  swtch(&p->context, &mycpu()->context);//这一次调用swich,不会返回到一条语句，而是返回到mycpu()->context->ra
  mycpu()->intena = intena;//scheduler"返回"到这里
}

void yield(void)
{
  struct proc *p = myproc();
  acquire(&p->lock);//调用的时候获得锁！ 多个cpu可能会同时访问p,所以需要锁
  p->state = RUNNABLE;
  sched();
  release(&p->lock);//释放从scheduler处获得的p->lock
}

```

## sleep与wakeup

- <font color=red>sleep 就是 把进程状态变成sleep,让回返回到scheduler</font>
- chan用于标记 因为sleep的原因，将来便于wakeup来筛选唤醒的进程。
- sleep 后需要放弃lk,防止死锁，唤醒后再次获得lk
- <font color=red>walkup就是把满足条件（匹配chan）的进程重新标注成Runable,这样scheduler就可以再次切换到这个进行</font>
```c
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();

  
  acquire(&p->lock);  //sleeplock1,获得锁，直到之后sched()切换完成之后
  release(lk);        //才会释放锁，保护了 p->state，p->chan ，这样才可以保证不会有,lost wakeup现象从出现

  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  release(&p->lock);//释放p->lock，这样wakeup可以修改进程的状态
  acquire(lk);//进入的时候获得lk,出去的时候也要获得lk 
}

void wakeup(void *chan)
{
  struct proc *p;

  for(p = proc; p < &proc[NPROC]; p++) {
    if(p != myproc()){
      acquire(&p->lock);
      if(p->state == SLEEPING && p->chan == chan) {
        p->state = RUNNABLE;
      }
      release(&p->lock);
    }
  }
}

```


## sleeplock
- 与acquires(lk)的区别是
- - 与acquires(lk):如果获得不了，阻塞，不放弃cpu,acquiresleep(lk),如果获得不了，放弃cpu
- - 与spinlock的另外一个区别是，不论是否获得lock, acquiresleep都不会"关闭中断"

```c
// Long-term locks for processes
struct sleeplock {
  uint locked;       // Is the lock held?
  struct spinlock lk; // spinlock protecting this sleep lock
};

void acquiresleep(struct sleeplock *lk)
{
    acquire(&lk->lk);
    while (lk->locked) {
        sleep(lk, &lk->lk);
    }
    lk->locked = 1;
    release(&lk->lk);
}

void releasesleep(struct sleeplock *lk)
{
    acquire(&lk->lk);
    lk->locked = 0;
    wakeup(lk);
    release(&lk->lk);
}
```