
## USB物理层
### USB数据线
| 导线名称 | 功能描述           | 颜色   | 电压/信号类型 |
|----------|--------------------|--------|---------------|
| VCC      | 提供电源给 USB 设备 | 红色   | 5V            |
| GND      | 提供电路的参考地   | 黑色   | -             |
| D+       | 传输数据的正极信号 | 绿色   | 数据正        |
| D-       | 传输数据的负极信号 | 白色   | 数据负        |

### USB总线的状态(p145)

USB 数据总线有多种状态，每种状态表示不同的信号和功能：

1. **J 状态**：
    - 数据线的默认状态。
    - 在空闲和数据传输之间切换。
2. **K 状态**：
    - 数据线的状态与 J 状态相反。
    - 用于表示特定的控制信号，如唤醒信号。
3. **SE0（Single Ended Zero）**：
    - D+ 和 D- 线都为低电平。
    - 用于表示数据包的结束或复位信号。

3. **Idle（空闲状态）**：
    - 数据线保持在 J 状态???。
    - 表示总线处于空闲状态，没有数据传输。

5. **Resume（恢复状态）**：
    - 用于从挂起状态恢复。
    - 通过发送特定的 K 状态信号来唤醒设备。

6. **SOP（Start of Packet）**：
    - 数据包的开始标志。
    - 从Idle状态变成K状态。

7. **EOP（End of Packet）**：
    - 数据包的结束标志。
    - 由一个 SE0 和两个 J 状态组成。
8. **RESET（复位状态）**：
    - 用于复位 USB 设备。
    - D+ 和 D- 线都保持低电平至少 10 毫秒。

### USB设备类型

1. **Hub（集线器）**：
    - Hub 是一种扩展设备，用于增加 USB 端口的数量，允许多个设备同时连接到主机。
    - Hub 本身也可以级联
    - Hub 设备通常具有以下特性：
        - **上行端口（Upstream Port）**：连接到主机或上一级 Hub。
        - **下行端口（Downstream Ports）**：连接到其他 USB 设备或下一级 Hub。
        - **电源管理**：可以为连接的设备提供电源，并管理电源分配。

2. **Function（功能设备）**：
    - 如键盘、鼠标、打印机、存储设备等。
    - 每个 Function 设备通过一个或多个端点（Endpoint）与主机通信。
    - Function 设备通常具有以下特性：
        - **<font color=red>设备描述符（Device Descriptor）**：描述设备的基本信息，如制造商、产品ID(VID,PID) 等。</font>
        - **配置描述符（Configuration Descriptor）**：描述设备的配置，包括电源需求、接口数量等。
        - **接口描述符（Interface Descriptor）**：描述设备的接口，每个接口对应一个功能。
        - **端点描述符（Endpoint Descriptor）**：描述设备的端点，每个端点对应一个数据传输通道。


    ### USB接口类型

    | 接口类型    | 描述                                                                 | 常见应用设备                         |
    |-------------|----------------------------------------------------------------------|--------------------------------------|
    | USB Type-A  |具有正反面之分,连接下游device。                       | 电脑、电视等设备                     |
    | USB Type-B  | 方形接口，通常用于打印机等外设,,连接上游host或者hub。   | 打印机等外设                         |
    | USB Type-C  | 新一代接口，对称设计，可以任意方向插入。支持更高的传输速率和功率传输。| 现代智能手机、笔记本电脑等设备       |
    ### USB设备的供电类型

    | 供电类型         | 描述                                                                 | 适用设备                   | 最大供电电流             |
    |------------------|----------------------------------------------------------------------|----------------------------|--------------------------|
    | Bus-Powered（总线供电） | 设备直接从 USB 总线获取电源。适用于低功耗设备。                       | 键盘、鼠标等               | 500mA（USB 2.0）或 900mA（USB 3.0） |
    | Self-Powered（自供电） | 设备有独立的电源，不依赖 USB 总线供电。适用于高功耗设备。               | 打印机、外部硬盘等         | -                        |
    | Dual-Powered（双重供电） | 设备可以同时支持总线供电和自供电，根据需要自动切换供电方式。提供更高的灵活性和兼容性。 | 各类设备                   | -                        |

### 传输模式

USB 设备的传输模式可以通过检测 D+ 和 D- 线路的电压来区分。具体原理如下：

1. **Low Speed（低速，1.5 Mbps）**：
  - D- 线上有上拉电阻（1.5kΩ）连接到 3.3V。
  - D+ 线保持低电平。

2. **Full Speed（全速，12 Mbps）**：
  - D+ 线上有上拉电阻（1.5kΩ）连接到 3.3V。
  - D- 线保持低电平。

3. **High Speed（高速，480 Mbps）**：
  - 初始时与 Full Speed 相同，D+ 线上有上拉电阻。
  - 在检测到高速握手信号后，设备会移除上拉电阻，并在 D+ 和 D- 线上发送高速信号。

4. **SuperSpeed（超高速，5 Gbps）**：
  - 使用独立的差分对（TX/RX）进行数据传输，不使用 D+ 和 D- 线。
  - 通过检测 SuperSpeed 差分对的信号来区分。

通过这些电压和信号特征，可以区分 USB 设备的传输模式。


## USB协议层


### <font color=red>USB 数据包字段格式(P195)</font>

USB 数据包由多个字段组成，每个字段都有特定的作用。以下是常见的 USB 数据包字段：

1. **SYNC（同步）**：
  - 用于同步发送和接收设备之间的时钟。
  - 在每个数据包的开头，长度为 8 位。
  - 编码为 `00000001`。

2. **PID（Packet Identifier）**：
  - 数据包标识符，用于标识数据包类型（如 IN、OUT、SETUP）。
  - 长度为 8 位。

3. **ADDR（Address）**：
  - 设备地址，用于指定目标设备。
  - 长度为 7 位。

4. **ENDP（Endpoint）**：
  - 端点号，用于指定目标设备的端点。
  - 长度为 4 位。

5. **CRC（Cyclic Redundancy Check）**：
  - 循环冗余校验，用于校验数据包的完整性。
  - 长度为 5 位（Token 包）或 16 位（Data 包）。

6. **DATA（数据）**：
  - 实际传输的数据。
  - 长度可变，最大为 8192 位。

7. **EOP（End of Packet）**：
  - 数据包结束标志。
  - 由一个 SE0（Single Ended Zero）和两个 J 状态组成。
  - 编码为 `00000000`???。


#### ENDP


EndPoint（端点）：
- 是USB 设备中的数据传输通道。
- 每个端点都有一个唯一的端点号（ENDP），用于标识该端点。端点号的长度为 4 位(0-15).
- EndPoint=0： 的端点通常被称为控制端点（Control Endpoint）。
控制端点用于传输控制类型的数据包，如设备描述符请求、配置请求等。
每个 USB 设备至少有一个控制端点（端点 0），用于初始化和配置设备。

EndPoint 与接口的关系
- 接口（Interface）：接口是 USB 设备中的一个逻辑分组，包含一组相关的端点。
每个接口可以包含多个端点。接口用于组织和管理端点，使得设备可以支持多种功能和数据传输类型。




EP 的用途:端点用于在主机和设备之间传输数据。

根据数据传输的方向和类型，端点可以分为以下几种：

- 控制端点（Control Endpoint）：用于传输控制数据，如设备配置和状态请求。
- 批量传输端点（Bulk Endpoint）：用于传输大量数据，如文件传输。
- 中断端点（Interrupt Endpoint）：用于传输小量数据，通常用于定期传输，如键盘和鼠标输入。
- 等时端点（Isochronous Endpoint）：用于传输实时数据，如音频和视频流。


### <font color=red>USB 数据包类型</font>

USB 通信使用多种类型的数据包，每种数据包都有特定的用途和结构。以下是常见的 USB 数据包类型：

1. **Token Packets（令牌包）**：
  - <font color=red>用于标识数据传输的方向和类型,用于开启事务</font>。
  - 包括三个子类型：
    - **IN**：主机请求从设备读取数据。
    - **OUT**：主机向设备发送数据。
    - **SETUP**：主机向设备发送控制信息。


    Token Packets 的格式如下：

    ```sh

    | PID (8 bits) | ADDR (7 bits) | ENDP (4 bits) | CRC5 (5 bits) |
    ```
2. **Start-of-Frame Packets（帧起始包）**：
  - 用于同步 USB 帧的开始。
  - 主要用于全速和高速 USB 设备，每毫秒发送一次。
    ```sh
    | PID (8 bits) | FRAMME_NUMBER (11 bits)| CRC5 (5 bits) |
    ```
  - <font color=pink>这个数据包周期性的发送，作为周期的刻度使用</font>
3. **Data Packets（数据包）**：
  - 用于传输实际的数据。
  - 包括两个子类型：
    - **DATA0**：数据包类型 0。
    - **DATA1**：数据包类型 1。
  - 在高速 USB 中，还包括 **DATA2** 和 **MDATA**。
```sh
 | PID (8 bits) | DATA (0-8192 bits) | CRC5 (16 bits) |
```
4. **Handshake Packets（握手包）**：
  - 用于确认数据传输的状态。
  - 包括三个子类型：
    - **ACK**：确认接收到数据。
    - **NAK**：暂时无法接收数据或数据不可用。
    - **STALL**：设备遇到错误，无法继续通信。
    - **NYET**: not yes,在 高速 USB 通信， 设备对ping消息的回复，没准备好。
```sh
 | PID (8 bits) |
```

5. **Special Packets（特殊包）**：
    - **PING,**：主机检查设备是否准备好接收数据,仅用于高速 USB 通信。。
    - **Ssplit,Csplit**：

通过这些数据包类型，USB 设备和主机能够进行有效的通信和数据传输。



### USB Transfer Types

USB 设备支持四种主要的传输类型，每种类型适用于不同的应用场景：
<font color=red>传输 由Stage组成，Stage由事务组成，事务由package组成。</font>
1. **Control Transfers（控制传输）**：
  - <font color=red>用于设备配置和控制,使用EndPoint 0进行通信</font>。
  - 典型应用：设备初始化、配置命令传输。

2. **Interrupt Transfers（中断传输）**：
  - 用于周期性的小数据量传输。
  - 典型应用：键盘、鼠标。
  - 特点：保证带宽和延迟，适合实时数据传输。





3. **Bulk Transfers（批量传输）**：
  - 用于大数据量的传输。
  - 典型应用：打印机、存储设备。
  - 特点：不保证带宽和延迟，但数据完整性高。




4. **Isochronous Transfers（等时传输）**：
  - 用于实时数据流传输。
  - 典型应用：音频、视频设备。
  - 特点：保证带宽和传输速率，但不保证数据完整性。

### USB Class 和 Transfer Type 的关系

USB 设备类（Class）定义了一组设备的通用行为和特性，每个类可以使用不同的传输类型来满足其需求。以下是一些常见的 USB 类及其使用的传输类型：

1. **HID（Human Interface Device）**：
  - 传输类型：Interrupt Transfers
  - 典型设备：键盘、鼠标

2. **Mass Storage**：
  - 传输类型：Bulk Transfers
  - 典型设备：U盘、外部硬盘

3. **Audio**：
  - 传输类型：Isochronous Transfers
  - 典型设备：麦克风、扬声器

4. **CDC（Communication Device Class）**：
  - 传输类型：Control Transfers, Bulk Transfers
  - 典型设备：调制解调器、网络适配器

5. **Video**：
  - 传输类型：Isochronous Transfers
  - 典型设备：摄像头

## Transfer 的组成

### <font color=red>Control Transfer 由3个事务（Transaction）组成:</font>

1. **Setup Transaction（设置事务）**：
    - <font color=gree>**SETUP 包**</font>：用于传输控制命令和请求。
    - <font color=gree>**DATA 包**</font>：包含请求的参数和数据。
    - **ACK 包**：确认接收到的数据。

2. **Data Transaction（数据事务）**（可选，根据请求类型）：
    - <font color=gree>**IN 包**或**OUT 包**</font>: 
    - <font color=pink>**DATA 包**</font>: ：传输实际的数据
    - <font color=yellow>**ACK 包**</font>：确认接收到的数据。

3. **Status Transaction（状态事务）**：
    - **IN 包**或**OUT 包**：用于传输状态信息，与数据事务数据包类型相反。
    - <font color=pink>**DATA 包**</font>:长度是0。
    - <font color=yellow>**ACK 包**</font>：确认接收到的状态信息。




### <font color=red>Interrupt Transfer 事务是IN 事务或者OUT 事务</font>

A. **IN 事务**： 比如host轮训鼠标位置，键盘按键
- <font color=gree>**IN 包**</font>：主机请求从设备读取数据。
- **DATA 包**：设备发送数据给主机。
- <font color=gree>**ACK 包**</font>：主机确认接收到的数据。

B. **OUT 事务**：比如host发送要打印的数据 给打印机
- <font color=gree>**OUT 包**</font>：主机向设备发送数据请求。
- <font color=gree>**DATA 包**</font>：主机发送数据给设备。
- **ACK 包**：设备确认接收到的数据。



### <font color=red>Bulk Transfers事务</font>

- LS,FS的过程与 Interrupt Transfer相同

- 在高速（High Speed）模式下，Bulk Transfers使用Ping协议来提高数据传输的效率和可靠性。Ping协议的主要作用是确认设备是否准备好接收数据，从而避免不必要的数据传输重试。以下是Ping协议的详细介绍：

A. **Ping 包**：
  - 主机发送一个Ping包给设备，询问设备是否准备好接收数据。

B. **NYET 包**：
  - 如果设备暂时无法接收数据，它会返回一个NYET（Not Yet）包，通知主机稍后再试。

C. **ACK 包**：
  - 如果设备准备好接收数据，它会返回一个ACK包，确认主机可以发送数据。
  - ACK包的格式如下：

D. **数据传输**：




### Split Transaction(p202)

Split Transaction 是一种用于 USB 2.0 及以上版本的技术，主要用于提高 USB 总线的效率，特别是在高速（High Speed）和低速（Low Speed）设备之间进行通信时。其主要用途如下：

1. **提高总线效率**：
    - 在高速 USB 总线上，低速设备的通信可能会占用较多的总线时间，影响其他高速设备的性能。Split Transaction 通过将低速设备的通信分成多个小的事务，减少了单次通信占用的总线时间，从而提高了总线的整体效率。

2. **减少延迟**：
    - 通过将一个大的数据传输任务分解成多个小的事务，可以减少每个事务的延迟，使得总线可以更快地响应其他设备的请求。

3. **支持多设备通信**：
    - Split Transaction 允许主机在处理一个低速设备的事务时，能够同时处理其他设备的请求，提高了多设备通信的并发性和效率。

4. **增强数据传输的可靠性**：
    - 通过分割数据传输任务，可以更好地管理和控制数据传输过程，减少数据传输中的错误和丢包现象，提高数据传输的可靠性。



Split Transaction 的实现通常涉及以下步骤：

1. **Start-Split（SSPLIT）**：
    - 主机向集线器发送一个 Start-Split 包，指示开始一个分割事务。

2. **Complete-Split（CSPLIT）**：
    - 集线器在完成低速设备的通信后，向主机发送一个 Complete-Split 包，指示分割事务的完成。
![alt text](img/s)


