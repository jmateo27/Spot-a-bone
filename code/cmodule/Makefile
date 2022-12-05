CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
# HOME = /home/avash
OUTDIR = $(HOME)/cmpt433/public/myApps/spotabone
SOURCES = main.c nfcReader.c myThreads.c button.c motionSensor.c common.c
CAMERA_DIR = ../camera
CAMERA_SOURCE = $(CAMERA_DIR)/camera.c
CAMERA_TARG = camera

all: clean main

main:
	mkdir -p $(OUTDIR)
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) -lpthread -lnfc
	

clean:
	rm -rf nfcReader *.o *~
