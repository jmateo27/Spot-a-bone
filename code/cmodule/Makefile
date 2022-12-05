CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
# HOME = /home/avash
OUTDIR = $(HOME)/cmpt433/public/myApps/spotabone
SOURCES = main.c nfcReader.c myThreads.c button.c motionSensor.c common.c
TARGET = main
FACERECOG_DIR = ../facerecog
CAMERA = $(FACERECOG_DIR)/camera.c

all: clean main

main: cmodule facerecognition createTextFiles
	@echo ""
	@echo "You must do the following to run everything:"
	@echo "(bbg)$$ cd /mnt/remote/myApps/spotabone/"
	@echo "(bbg)$$ make"
	@echo "(bbg)$$ ./camera"
	@echo "(bbg)$$ ./main"
	@echo "(bbg)$$ python3 facerecog.py"
	@echo "(bbg)$$ python3 main.py"

cmodule:
	mkdir -p $(OUTDIR)
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) -lpthread -lnfc

facerecognition:
	cp -r $(CAMERA) $(OUTDIR)
	mkdir -p $(OUTDIR)/photos
	cp -r $(FACERECOG_DIR)/* $(OUTDIR)

createTextFiles:
	mkdir -p $(OUTDIR)/comms
	: > $(OUTDIR)/comms/name.txt
	: > $(OUTDIR)/comms/analyzeFace.txt
	: > $(OUTDIR)/comms/camera.txt
	: > $(OUTDIR)/comms/NFC.txt
	: > $(OUTDIR)/comms/takePhotos.txt

clean:
	rm -rf nfcReader *.o *~
