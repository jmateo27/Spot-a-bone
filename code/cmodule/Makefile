CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
OUTDIR = $(HOME)/cmpt433/public/myApps/spotabone
SOURCES = *.c
# SOURCES = main.c nfcReader.c myThreads.c button.c motionSensor.c common.c
TARGET = main

TESTING = testing
TEST_SOURCES = $(TESTING)/nfcTest.c $(TESTING)/nfc-utils.c

all: clean cmodule createTextFiles
	@echo "Made cmodule"

cmodule:
	mkdir -p $(OUTDIR)
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) -lpthread -lnfc
	$(CC_C) $(CFLAGS) $(TEST_SOURCES) -o $(OUTDIR)/nfcTest -lnfc

createTextFiles:
	mkdir -p $(OUTDIR)/comms
	: > $(OUTDIR)/comms/takePhotos.txt
	: > $(OUTDIR)/comms/camera.txt
	: > $(OUTDIR)/comms/name.txt
	: > $(OUTDIR)/comms/NFC.txt

clean:
	rm -rf nfcReader *.o *~
