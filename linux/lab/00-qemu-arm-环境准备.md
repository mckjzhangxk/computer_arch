[视频教程](https://www.bilibili.com/video/BV1PJ411m7fs/?spm_id_from=333.788.recommend_more_video.-1&vd_source=ba17c91d27a087001a89289fd2c2af49)
## 环境准备
```sh
# 3.qemu环境安装
sudo apt install qemu-system
sudo apt install gcc-arm-linux-gnueabi
sudo apt install -y bison flex libssl-dev u-boot-tools
```

## mac 环境
```sh
#查看所有的arm包
brew search ^arm

#arm软件源添加
brew tap ArmMbed/homebrew-formulae

 

# arm32安装
brew install arm-none-eabi-gcc
brew install arm-none-eabi-binutils
brew install arm-none-eabi-gdb

# arm64安装
brew install aarch64-elf-binutils 
brew install aarch64-elf-gcc
brew install aarch64-elf-gdb



# x86-64 安装
brew install x86_64-elf-binutils
brew install x86_64-elf-gcc
brew install x86_64-elf-gdb


brew install qemu


#risv 安装,以下方法可能不管用
#riscv软件源添加
brew tap riscv/riscv
brew install riscv-tools

```