## 基本概念

- package: 软件的组成以package为单位。存放在package/{name}下面
- <font color=gree>package的定义：package/{name}下有以下文件:
- - Config.in:  菜单的定义，配置变量的定义
- - ${name}.mk: 软件的【构建与安装】命令</font>
- output：构建的输出目录
- - host:  可以理解成：本机构建的sysroot(tool chain)
- - target: 目标文件系统(不是最终版本)
- - images: Image,rootfs.ext4,start-qemu.sh
- - build: 中间文件，比如解压出来的源码，编译好的文件
- dl: 下载的包 缓存在此处。
## 外部包的引入
```sh
|--externel
|   |
|   |--- Config.in #定义所有 packages
|   |--- external.desc # project name
|   |--- external.mk  # 包括所有构建 脚本
|   |--- configs      #可选，当前的配置.config
|   |--- package
    |     |--- $ package1  -- package1.mk,Config.in
    |     |----$ package2  -- package2.mk,Config.in
|--buildroot
```
- 外部包是说 package的位置 不在buildroot目录中，如上面的externel
- [external.desc](external/base_external/external.desc): <font color=red>定义了packet集合的name, BR2_EXTERNAL_${name}_PATH 执行 最外层的目录(external)</font>
- [Config.in](external/base_external/Config.in):  引入所有 packages
- [external.mk](external/base_external/external.mk):引入所有 packages 构建方法
- [包的构建](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)，generic-package-reference构架跨平台target,host-generic-package构建本地target


## 构建命令

- 配置命令： 生成的配置文件保存在.config下面，下面的环境变量只需输入一遍
```sh
# 1.-C buildroot:进入 buildroot
# 2.BR2_EXTERNAL=${EXTERNAL} :设置外部package路径
# 3. make defconfig BR2_DEFCONFIG=${DEFFILE_CONF}: 启用默认配置，${DEFFILE_CONF}最为默认配置的 路径
make -C buildroot defconfig BR2_EXTERNAL=${EXTERNAL} BR2_DEFCONFIG=${DEFFILE_CONF}

```
- 另存为配置
```sh
make -C buildroot savedefconfig BR2_DEFCONFIG=${save_path}
```
- 修改配置：
```sh
make menuconfig
```
- 清理配置
```sh
# 删除.config文件
make -C buildroot distclean
```

- 编译
```sh
cd buildroot
# 构建全部
make 
# 个别构建： 目标对应package/aesd-assignmentsaesd-assignments.mk？
make aesd-assignment
```

### ReBuild

```sh
# 方法1：

# 目标对应package/aesd-assignmentsaesd-assignments.mk？
make aesd-assignments-rebuild 
make aesd-assignments-reconfigure


#方法2：本地构建

export ESD_ASSIGNMENTS_OVERRIDE_SRCDIR= /path/to/local

# 加速编译
export  BR2_DL_DIR =<软件包缓存位置>

```

- <font color=pink>.mk文件不存放任何源代码，而是 配置如何下载源码，如何编译源码，如何安装编译后的文件</font>

-  参考 [aesd-assignments.mk](external/base_external/package/aesd-assignments/aesd-assignments.mk),[install命令](https://linux.die.net/man/1/install)




```sh

# 使用git的方式下载源代码 
{name}_VERSION = 'main`:'
{name}_SITE = 'git@github.com:cu-ecen-aeld/assignment-4-mckjzhangxk.git'
{name}_SITE_METHOD = git
{name}_SUBMODULES = YES


# 安装命令总结 
# 创建目标文件夹（mkdir -p）
install -d $(TARGET_DIR)/etc/finder-app/conf/
# source 拷贝到 TARGET_DIR下
install -m 0755 $(SOURCE) $(TARGET_DIR)
# source 拷贝到 TARGET,TARGET是文件而不是目录
install -m 0755 -T $(SOURCE) $(TARGET)
```

###  软件包的安装
- 先在 buildroot/package/Config.in查看需要的软件包菜单。然后执行make menuconfig
- eg :Networking application ->dropbear （ssh）


```sh
# 网络端口映射 10022->22， 2222->2222
qemu-system-aarch64 \
    -M virt  \
    -cpu cortex-a53 -nographic -smp 1 \
    -kernel buildroot/output/images/Image \
    -append "rootwait root=/dev/vda console=ttyAMA0" \
    -netdev user,id=eth0,hostfwd=tcp::10022-:22,hostfwd=tcp::2222-:2222 \
    -device virtio-net-device,netdev=eth0 \
    -drive file=buildroot/output/images/rootfs.ext4,if=none,format=raw,id=hd0 \
    -device virtio-blk-device,drive=hd0 -device virtio-rng-pci \

# 不用收到输入密码
sshpass  -p <passwd> ssh root@127.0.0.1 -p 10022
sshpass  -p <passwd> scp -P 10022 root@127.0.0.1:/tmp/resolv.conf .
```

