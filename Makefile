DRIVER_DIR = ./driver
LIB_DIR = ./lib
USR_DIR = ./user_app


export DIR=$(PWD)

all:
	make -C $(DRIVER_DIR)
	make -C $(LIB_DIR)
	make -C $(USR_DIR)


clean:
	make -C $(DRIVER_DIR) clean
	make -C $(LIB_DIR) clean
	make -C $(USR_DIR) clean