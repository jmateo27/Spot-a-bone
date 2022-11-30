CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -pthread

all: clean test
	cp test $(HOME)/cmpt433/public/myApps/

test: test.o 
	$(CC_C) $(CFLAGS) -o test test.o 

test.o:
	$(CC_C) $(CFLAGS) -c test.c

grabber.o:
	$(CC_C) $(CFLAGS) -c grabber.c

clean:
	rm -rf test *.o *~
