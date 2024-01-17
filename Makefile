DRIVER_DIR = ./driver
LIB_DIR = ./lib


export DIR=$(PWD)

all:
	make -C $(DRIVER_DIR)
	make -C $(LIB_DIR)


clean:
	make -C $(DRIVER_DIR) clean
	make -C $(LIB_DIR) clean
