![plic.png](imgs%2Fplic.png)
- PLIC:platform interrupt Controller,相当于一个中断的路由器
- PLIC连接53根外部设备的 中断总线
- 每个cpu core通过编程的方式 告诉plic，我对那个中断感兴趣。

### cpu关于中断的寄存器
| 寄存器            | 描述                 |
|----------------|--------------------|
| sstatus        | 当前的level,当前是否允许中断？ |
| sie            | 异常中断的使能            |
| stvec          | 异常中断的处理handler     |
| sepc     | 触发异常时候正在执行的pc |

241100701130010