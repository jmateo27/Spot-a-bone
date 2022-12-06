#ifndef MYTHREADS_H_
#define MYTHREADS_H_

#include <pthread.h>
#include <string.h>

#include "nfcReader.h"
#include "button.h"
#include "timing.h"
#include "communication.h"
#include "lcd.h"
#include "lightDipAnalyzer.h"

void *threadNFC(void *arg);

void *threadCameraButton(void *arg);

void *threadLCDScreen(void *args);

#endif
