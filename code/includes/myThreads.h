#ifndef MYTHREADS_H_
#define MYTHREADS_H_
#include <pthread.h>
#include "nfcReader.h"
#include "motionSensor.h"
#include "socketIO.h"
#include <time.h>

void *threadNFC(void *arg);

void *threadMotionSensor(void *arg);

void sleepForMs(long long delayInMs);

#endif