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
	@echo "Ran camera, cmodule and face recognition programs"
	
clean:
	rm -rf $(TARGET)
