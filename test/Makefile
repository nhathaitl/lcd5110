
INCLUDE_DIR=../lib
CFLAGS=-I$(INCLUDE_DIR) -Wall
LDFLAGS=-L$(INCLUDE_DIR) -l lcd_lib

TARGET=tlnt_lcd
CC=arm-linux-gnueabi-gcc
#CC=gcc

all:
	$(CC) test_lcd.c $(CFLAGS) $(LDFLAGS) -o $(TARGET) -static


clean:
	rm $(TARGET) 
