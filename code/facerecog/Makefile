CC_C = gcc
CFLAGS = 
SOURCE = camera.c
TARGET = camera

all: clean
	$(CC_C) $(SOURCE) -lv4l2 -o $(TARGET)

run:
	./camera
	./main
	python3 facerecog.py
	
clean:
	rm -rf $(TARGET)
