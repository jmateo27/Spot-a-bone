#include "includes/myThreads.h"

#define oneMin 1

void *threadNFC(void *arg){
    NFC_descriptor *descPtr = (NFC_descriptor *) arg;
    int tagNum = 0, prevTagNum = 0;
    NFC_initialize(descPtr);
    while(1){
        if ((tagNum = NFC_poll(descPtr)) != prevTagNum && tagNum != 0){
            printf("Found tag #%d\n", tagNum);
            if (tagNum != 0)
                prevTagNum = tagNum;
            NFC_queueUp(tagNum);
        }
    }
    return NULL;
}

void *threadMotionSensor(void *arg){
    motionSensor_initiate();
    printf("Calibrating motion sensor\n");
    sleep(oneMin*60*1000);
    printf("Finished calibrating motion sensor\n");
    int motion = 0;
    while(1){
        motion = motionSensor_isThereMotion();
        if (motion == 1){
            printf("Motion detected!\n");
        }
    }
    return NULL;
}