
INCLUDE_DIR=../lib
CFLAGS=-I$(INCLUDE_DIR) -Wall
LDFLAGS=-L$(INCLUDE_DIR) -l lcd_lib

TARGET=app_snake_hunting
CC=arm-linux-gnueabi-g++

all:
	$(CC) main.cpp $(CFLAGS) $(LDFLAGS) -o $(TARGET) -static


clean:
	rm $(TARGET) 
