#ifndef MYTHREADS_H_
#define MYTHREADS_H_
#include <pthread.h>
#include "nfcReader.h"
#include "motionSensor.h"

void *threadNFC(void *arg);

void *threadMotionSensor(void *arg);

#endif