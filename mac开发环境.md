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