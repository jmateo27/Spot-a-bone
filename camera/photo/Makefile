CC_C = g++-arm-linux-gnueabihf
CFLAGS = -Wall -g  -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -pthread

all: clean camera
	cp camera $(HOME)/cmpt433/public/myApps/

test: camera.o 
	$(CC_C) $(CFLAGS) -o camera camera.o 

camera.o:
	$(CC_C) $(CFLAGS) -c camera.cpp

# capture.o:
# 	$(CC_C) $(CFLAGS) -c capture.c

clean:
	rm -rf test *.o *~
