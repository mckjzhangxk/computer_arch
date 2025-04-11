

```sh
# 查看usb控制器 
lspci|grep USB
# 00:14.0 USB controller: Intel Corporation 8 Series/C220 Series Chipset Family USB xHCI (rev 04)
# 00:1a.0 USB controller: Intel Corporation 8 Series/C220 Series Chipset Family USB EHCI #2 (rev 04)
# 00:1d.0 USB controller: Intel Corporation 8 Series/C220 Series Chipset Family USB EHCI #1 (rev 04)

# 查看对应的 控制器设备
cd /sys/bus/pci/devices
ls -l 00:00:14.0 
```
||||
|-|-|-|
|EHCI|Enhanced Host Controller Interface|Enhanced Host Controller Interface	USB 2.0	专门用于管理 USB 2.0 高速设备（480 Mbps）。|
|xHCI|Extensible Host Controller Interface|设计用于支持 USB 3.0（5 Gbps）及更高版本，同时也向下兼容 USB 2.0。|




### Bus、Port 和设备的关系
- bus controller 管理 bus。 一般 dev=1的设备对应总线控制器。
```sh
  bus 01:  ============================================
           |                     |                    |
           Controller(dev=1)     mouse(dev=3)        hub(dev=8)


  bus 02:  ============================================
           |                     |                    |
           Controller(dev=1)     adb(dev=13)        hub(dev=28)


# 查看总线与控制器的关系
ls -l /sys/bus/usb/devices/usb*
```  
- bus下面可以有 多个 port
- port 对应 设备,Port 是每个 Bus 上设备的具体物理连接位置。
在输出中，Bus 和 Port 的关系如下：

```sh

lsusb -s $bus:$dev  #查看总线 上的设备
lsusb -d $vender:$product  #根据 。。。 查看
lsusb -v  #全部的详细信息
lsusb -t #树形结构


```


### 设备的查看


```sh
# 查看控制器设备， 其中 iSerial表示 /sys/bus/pci/devices下面的设备
lsusb -s 03:01
# 结构
#   bcdUSB               2.00
#   bDeviceClass            9 Hub
#   idVendor           0x1d6b Linux Foundation
#   idProduct          0x0002 2.0 root hub
#   bcdDevice            5.15
#   iManufacturer           3 Linux 5.15.0-134-generic xhci-hcd
#   iProduct                2 xHCI Host Controller
#   iSerial                 1 0000:00:14.0

# 查看荣耀设备 iSerial会作为 adb devices的输出
lsusb -s 03:20

#   bDescriptorType         1
#   bcdUSB               2.10
#   bMaxPacketSize0        64
#   idVendor           0x339b
#   idProduct          0x107d
#   bcdDevice            5.15
#   iManufacturer           1 HONOR
#   iProduct                2 PGT-AN00
#   iSerial                 3 A9FFVB3802000616


# Usb设备预览。 其中 命名规则是 $bus-$port:子编号
ls /sys/bus/usb/devices

# usb设备使用的驱动，与lsmod结合看
ls /sys/bus/usb/drivers
```


||||
|-|-|-|
|idVendor|	设备的供应商 ID。
|idProduct|	设备的产品 ID。
|bDeviceClass|	设备的类别（如 Mass Storage、HID）。
|bDeviceSubClass|	设备子类别。
|bDeviceProtocol|	设备的协议类型。
|bMaxPacketSize0|	设备控制端点（端点 0）的最大包大小。
|bNumConfigurations|	设备支持的配置数量。
|iManufacturer|	制造商字符串的索引。
|iProduct|	产品字符串的索引。
|iSerial|	序列号字符串的索引。
|bmAttributes|	设备电源属性（如自供电或总线供电）。
|MaxPower|	设备最大电流需求（单位为 2mA）。
|bEndpointAddress|	端点地址和方向（如 IN/OUT）。
|bmAttributes|	端点的传输类型（如控制、中断、等时、批量）


### usb 版本
||||
|-|-|-|
|5000M：|表示设备工作在 USB 3.0 模式（5 Gbps）。
|480M：|表示设备工作在 USB 2.0 模式（480 Mbps）。
|12M：|表示设备工作在 USB 1.1 全速模式（12 Mbps）。

