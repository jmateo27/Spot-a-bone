CC_C = gcc
CFLAGS = 
SOURCE = camera.c
TARGET = camera

all: clean
	$(CC_C) $(SOURCE) -lv4l2 -o $(TARGET)
	
clean:
	rm -rf $(TARGET)
