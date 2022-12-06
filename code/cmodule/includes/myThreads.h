#ifndef MYTHREADS_H_
#define MYTHREADS_H_

#include <pthread.h>

#include "nfcReader.h"
#include "motionSensor.h"
#include "button.h"
#include "timing.h"
#include "communication.h"

void *threadNFC(void *arg);

void *threadCameraButton(void *arg);

#endif
