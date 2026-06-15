ARCH = arm
CROSS_COMPILE = arm-linux-gnueabihf-

KERNEL_DIR = $(PWD)/qemu-pi-setup/linux

obj-m += driver.o

# LA SOLUCIÓN DEFINITIVA: Desactivamos ftrace, pg, y profiling por completo
CFLAGS_REMOVE_driver.o := -pg
ccflags-y := -fno-optimize-sibling-calls -fno-omit-frame-pointer

all:
	make -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean