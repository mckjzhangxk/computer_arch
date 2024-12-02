## ISA
- RISC-V 是指令的规范（ISA）
- <font color=red>命名规范 RV{32/64/128}{I M A F D C},其中32,64，128表示寄存器长度,{I M A F D C}表示支持的模块</font>
- 指令长度都是 32位

## 模块化
- RISC ISA = 1 个基本整数指令集 + 多个可选的扩展指令集
- <font color=red>基本整数指令集： 32I，32E,64I,128I，其中32E表示32位嵌入式指令。128I要兼容64I，64I要兼容32I
- 扩展指令</font>

| 扩展指令 | 描述            |
|------|---------------|
| M    | 乘法指令          |
| A    | 原子指令          |
| F    | 单精度浮点指令       |
| D    | 双精度浮点指令       |
| C    | 压缩指令（指令长度<32） |
- 使用代号G 表示 M+A+F+D，例如RV64GC(就是支持以上全部)

## HART
- hardware thread
- 代表【指令执行流】，意思就是 独立完成【fetch】->【decode】->【execute】的独立单元
- RISC-V使用HART概念 来区分硬件实现上的多核，多线程
## 分层设计
- M,S,U三个级别
- M级别特权最高，S级别相当于保护级别，U是用户级别
- M级别不开启VM， S,U级别开启VM，只有支持S级别的cpu才可以实现进程的概念。
- <font color=red>不同级别体现在对 CSR(CONTROL STATUS REGISTER）寄存器 获取与设置
- M,S,U分别有对应级别的CSR。eg:mstatus,sstatus,ustatus</font>
- 高级别 可以访问低级别 模式的CSR，反之不可
- 常用成CSR:以S模式为例

1.设置trap用到的寄存器

  | 寄存器            | 描述                 |
  |----------------|--------------------|
  | sstatus        | 当前的level,当前是否允许中断？ |
  | sie            | 异常中断的使能            |
  | stvec          | 异常中断的处理handler     |


2.处理trap用到的寄存器


  | 寄存器      | 描述                                      |
  |-|-|
  | sscratch |                                         |
  | sepc     | 触发异常时候正在执行的pc                           |
  | sip      | 等待处理的异常，<font color=pink>记录是否被触发</font> |
  | sscause  | 异常的原因                                   |
  | stval    | 造成异常的数值                                 |


  
  | 寄存器  | 描述              |
  |- |- |
  | stap | 保存vm table的物理地址 |
3. sip、sie的结构
- 两者结构完全相同，sie是使能位，sip是标志位
- sip,sie下的中断分成3类:software(SIP),timer(TIP),external(EIP)
- sip,sie下的中断分两种模式，U/S
- 所以结合上面，有6中中断 SSIP,USIP,STIP,UTIP,SEIP,UEIP,见手册74页

4 sstatus的结构:见手册68页
- sie 位，是所有中断的使能位， 1-开启，0-关闭
- spie位, 当trap发生 或者trap返回的时候临时存储sie位
- - trap发生： 设置 spie=sie, sie=0,此时不会再触发中断。
- - sret执行： 设置 sie=spie, spie=0, 恢复之前的sie位
- spp: <font color=gree>记录trap发生之前 cpu的模式
- - usermode -> supermode, 设置spp=0
- - supermode -> supermode, 设置spp=1</font>
- spp <font color=orange>在sret执行时候，并根据spp，确定返回的模式
- -  if spp=0, sret--->usermode
- -  if spp=1, sret--->supermode </font>