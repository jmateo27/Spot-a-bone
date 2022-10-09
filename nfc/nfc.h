#ifndef NFC_H_
#define NFC_H_

#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
#include<unistd.h>
#define BUFFER_SIZE 19 //0x00 to 0x13

int bcdToDec(char b);

#endif