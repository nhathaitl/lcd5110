obj-m := lcd_driver.o
lcd_driver-objs := lcd_ctrl.o lcd_5110.o

BBB_KERNEL := /home/norman/bbb/kernelbuildscripts/KERNEL
TOOLCHAIN := /home/norman/bbb/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

all: 
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN) -C $(BBB_KERNEL) M=$(shell pwd) modules
	
clean:
	make -C $(BBB_KERNEL) M=$(shell pwd) clean
