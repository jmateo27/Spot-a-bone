#ifndef NFCREADER_H_
#define NFCREADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <nfc/nfc.h>

// Tag 1
// 04  86  6a  b1  70  00  00 

// Tag 2
// 04  87  6a  b1  70  00  00

typedef struct{
    int tagNumber;
    uint8_t UID[7];
} tagWithUID;

tagWithUID tagDatabase[] = {
    {1, {0x04, 0x86, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
    {2, {0x04, 0x87, 0x6a, 0xb1, 0x70, 0x00, 0x00}}
};

int numTags = 2;

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"

#define I2C_DEVICE_ADDRESS 0x24

#define REG_OUT 0x86
int findOutWhichTag(const uint8_t *pbtData, const size_t szBytes);
// static void print_hex(const uint8_t *pbtData, const size_t szBytes);
void runCommand(char* command);

#endif