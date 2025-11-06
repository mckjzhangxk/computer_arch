ifeq ($(KERNELRELEASE),) # 第一次 KERNELRELEASE 没有被设置的时候

ifeq ($(ARCH),arm)
KERNELDIR ?= /home/hack520/project/linux-5.10.99
ROOTFS ?= /opt/4412/rootfs
else
# sudo apt install --reinstall linux-headers-$(uname -r)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
endif
PWD := $(shell pwd)

modules:  # 执行下面命令
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules INSTALL_MOD_PATH=$(ROOTFS) modules_install

clean:
	rm -rf  *.o  *.ko  .*.cmd  *.mod.*  modules.order  Module.symvers   .tmp_versions *.mod *.d

else	# 第二次 执行 make  -C $(KERNELDIR) M=$(PWD) modules 的时候进入

# 注意依赖的顺序
obj-m += my_hello.o
obj-m += my_param.o
obj-m += my_register_dev.o
obj-m += my_error_dev.o
obj-m +=io_poll_demo_retcode.o

obj-m += my_cdev.o
obj-m += my_cdev_read_write.o
obj-m += my_cdev_read_write_obj.o
obj-m +=my_cdev_read_write_ioctl.o

obj-m +=io_none_block_demo.o
obj-m +=io_block_demo.o
obj-m +=io_poll_demo.o
obj-m +=io_signal_demo.o

obj-m +=my_cdev_atomic.o
obj-m +=my_cdev_spinlock.o
obj-m +=my_cdev_sem.o
obj-m +=my_cdev_timer.o


obj-m +=my_cdev_led.o
obj-m +=my_cdev_led_dt.o


#数据结构 demo
obj-m +=struct_list_demo.o
obj-m +=struct_rb_tree_demo.o

# 如果有多个源文件(a.o,b.o,c.o)组成一个 fun.o，需要这么写：
# obj-m += func.o
# func-objs = a.o b.o c.o
endif

