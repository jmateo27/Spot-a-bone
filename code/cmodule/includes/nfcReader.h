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

#include "common.h"

#define UID_len 7

typedef struct{
	int tagNum;
	bool isSong;
} tag;

typedef struct
{
    tag theTag;
    uint8_t UID[7];
} tagWithUID;

typedef struct
{
    nfc_device *dev;
    nfc_target targ;
    nfc_context *cont;
} NFC_descriptor;

void NFC_init(NFC_descriptor *desc);
void NFC_poll(NFC_descriptor *desc, tag* theTag);
void NFC_findOutWhichTag(const uint8_t *pbtData, const size_t szBytes, tag* theTag);
void NFC_cleanup(NFC_descriptor *desc);
// void NFC_queueUp(int tagNum);

#endif