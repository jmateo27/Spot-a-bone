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

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"

#define I2C_DEVICE_ADDRESS 0x24

#define REG_OUT 0x86

// static int initI2cBus(char* bus, int address);
// void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);
// static unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr);
static void print_hex(const uint8_t *pbtData, const size_t szBytes);
void runCommand(char* command);

#endif