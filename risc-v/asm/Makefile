#设置需要调试的目标
TARGET=ld_st/store


CC= riscv64-unknown-elf-gcc 
CFLAGS=-nostdlib -fno-builtin -march=rv32g -mabi=ilp32 -Ttext=0x80000000 -g


QUME=qemu-system-riscv32
QFLAGS=-nographic -smp 1 -machine virt -bios none  -s -S

GDB=riscv64-unknown-elf-gdb
GFLAGS=-x .gdbinit


build:
	${CC} ${CFLAGS} ${OBJS} ${TARGET}.s -o ${TARGET}.elf

qemu: build
	${QUME} ${QFLAGS} -kernel ${TARGET}.elf

debug:
	${GDB} ${GFLAGS} ${TARGET}.elf

clean:
	rm */*.elf