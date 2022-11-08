CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
HOME = /home/jmateo

all: clean nfcReader deploy

nfcReader: nfcReader.o nfc-utils.o
	$(CC_C) $(CFLAGS) -o nfcReader nfcReader.o nfc-utils.o -lm -lnfc

nfc-utils.o:
	$(CC_C) $(CFLAGS) -c utils/nfc-utils.c

nfcReader.o:
	$(CC_C) $(CFLAGS) -c nfcReader.c

deploy:
	cp nfcReader $(HOME)/cmpt433/public/myApps/

clean:
	rm -rf nfcReader *.o *~
