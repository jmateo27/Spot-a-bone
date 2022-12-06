TARGET= lcd
SOURCES= gpio.c lcd.c

OUTDIR = $(HOME)/cmpt433/public/myApps
CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

all:
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)
	cp export_pins.sh $(OUTDIR)