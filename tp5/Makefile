ARCH         = arm
CROSS_COMPILE = arm-linux-gnueabihf-
KERNEL_DIR   = $(PWD)/rpi-linux

obj-m += driver.o

CFLAGS_REMOVE_driver.o := -pg
ccflags-y := -fno-pic -mno-single-pic-base -fno-common \
             -fno-delete-null-pointer-checks -O2

all:
	make -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean