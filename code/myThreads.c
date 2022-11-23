#include "includes/myThreads.h"

#define oneMin 1

void *threadNFC(void *arg)
{
    NFC_descriptor *descPtr = (NFC_descriptor *)arg;
    int tagNum = 0, prevTagNum = 0;
    NFC_initialize(descPtr);
    char str[2];
    while (1)
    {
        
        if ((tagNum = NFC_poll(descPtr)) != prevTagNum && tagNum != 0)
        {
            printf("Found tag #%d\n", tagNum);
            if (tagNum != 0)
                prevTagNum = tagNum;
            NFC_queueUp(tagNum);
            sprintf(str, "%d\n", tagNum);
            Socket_send()
        }
    }
    return NULL;
}

void *threadMotionSensor(void *arg)
{
    motionSensor_initiate();
    printf("Calibrating motion sensor\n");
    sleepForMs(10);
    printf("Finished calibrating motion sensor\n");
    int motion = 0, pirState = 0;
    while (1)
    {
        motion = motionSensor_isThereMotion();
        if (motion == 1)
        {
            if (pirState == 0)
            {
                printf("Motion detected!\n");
                pirState = 1;
            }
        }
        else
        {
            if (pirState == 1)
            {
                printf("Motion ended!\n");
                pirState = 0;
            }
        }
    }
    return NULL;
}

void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}