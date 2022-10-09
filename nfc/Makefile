CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
HOME = /home/jmateo

all: nfc deploy

run: nfc
	./nfc

hello:
	$(CC_C) $(CFLAGS) nfc.c -o nfc

# nfc.o:
# 	$(CC_C) $(CFLAGS) -c nfc.c

deploy:
	cp nfc $(HOME)/cmpt433/public/myApps/

clean:
	rm -rf nfc *.o *~
