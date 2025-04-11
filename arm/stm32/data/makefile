# arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -c mystartup.s
# arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -ffreestanding -DSTM32F10X_MD -c -I include main.c
# arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -ffreestanding -DSTM32F10X_MD -fvisibility=hidden -c -I include lib/system_stm32f10x.c
# arm-none-eabi-ld -T stm32.ld -o output.elf mystartup.o main.o system_stm32f10x.o

# 编译器和链接器
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld

# 目标架构参数
MCU = -mcpu=cortex-m3 -mthumb
CFLAGS = $(MCU) -ffreestanding -DSTM32F10X_MD -I include -fvisibility=hidden
ASFLAGS = $(MCU)

# 链接脚本
LDSCRIPT = stm32.ld

# 源文件和目标文件
SRCS = startup.s main.c lib/system_stm32f10x.c
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)

# 目标文件
TARGET = myled.elf

# 生成规则
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -T $(LDSCRIPT) -o $@ $^

%.o: %.s
	$(CC) $(ASFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标文件
clean:
	rm -f $(OBJS) $(TARGET)
