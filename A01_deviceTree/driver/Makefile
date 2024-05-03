KERNELDIR := /home/xqyr/study/new_study/xiong_lib/linux-imx-rel_imx_4.1.15_2.1.0_ga
CURRENT_PATH := $(shell pwd)
LINUX_PATH := /home/xqyr/study/new_study/flie/nfs/root
name  = charled

obj-m += ${name}.o

charled-objs := main_file.o chardevice.o linux_gpio.o main.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH)  modules
all:
	 make -C $(KERNELDIR) M=$(CURRENT_PATH)  modules
cp:
	sudo cp $(CURRENT_PATH)/${name}.ko ${LINUX_PATH}/lib/modules/4.1.15/
	make clean
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH)  clean