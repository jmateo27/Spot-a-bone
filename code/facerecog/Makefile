CC_C = gcc
CFLAGS = 
SOURCE = camera.c
TARGET = camera

all: clean
	$(CC_C) $(SOURCE) -lv4l2 -o $(TARGET)

run: camera cmodule facerecog
	@echo "Ran camera, cmodule and face recognition programs"
	
camera:
	./camera

cmodule:
	./main

facerecog:
	python3 facerecog.py

clean:
	rm -rf $(TARGET)
