ifeq ($(KERNELRELEASE),)

ifeq ($(ARCH),arm)
KERNELDIR ?= /home/hack520/project/linux-5.10.99
ROOTFS ?= /opt/4412/rootfs
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
endif
PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules INSTALL_MOD_PATH=$(ROOTFS) modules_install

clean:
	rm -rf  *.o  *.ko  .*.cmd  *.mod.*  modules.order  Module.symvers   .tmp_versions

else
obj-m += zxkhello.o
obj-m += param.o

# 注意依赖的顺序
obj-m += module1.o
obj-m += module2.o


obj-m += register_dev.o

obj-m += my_cdev.o
obj-m += my_cdev_read_write.o
obj-m += my_cdev_read_write_obj.o
obj-m +=my_cdev_read_write_ioctl.o
obj-m +=none_block_demo.o
obj-m +=block_demo.o
obj-m +=poll_demo.o
obj-m +=signal_demo.o
obj-m +=my_cdev_atomic.o
obj-m +=my_cdev_spinlock.o
obj-m +=my_cdev_sem.o
obj-m +=my_cdev_timer.o
# 如果有多个源文件(a.o,b.o,c.o)组成一个 fun.o，需要这么写：
# obj-m += func.o
# func-objs = a.o b.o c.o
endif

