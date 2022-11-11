CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
HOME = /home/jmateo
OUTDIR = $(HOME)/cmpt433/public/myApps
SOURCES = main.c nfcReader.c myThreads.c button.c motionSensor.c
TARGET = main

all: clean main

main:
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) -lpthread -lnfc

clean:
	rm -rf nfcReader *.o *~
