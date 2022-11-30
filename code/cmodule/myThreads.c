#include "includes/myThreads.h"
#include "includes/button.h"
#include "includes/camera.h"

#define oneMin 1

void *threadNFC(void *arg)
{
    NFC_descriptor *descPtr = (NFC_descriptor *)arg;
    int tagNum = 0, prevTagNum = 0;
    NFC_init(descPtr);
    while (1)
    {

        if ((tagNum = NFC_poll(descPtr)) != prevTagNum && tagNum != 0)
        {
            printf("Found tag #%d\n", tagNum);
            if (tagNum != 0)
                prevTagNum = tagNum;
            NFC_queueUp(tagNum);
        }
    }
    return NULL;
}

void *threadMotionSensor(void *arg)
{
    MotionSensor_init(left);
    // MotionSensor_init(right);
    printf("Calibrating motion sensors\n");
    sleepForMs(1000);
    printf("Finished calibrating motion sensor\n");
    int motion = 0, pirState = 0;
    while (1)
    {
        motion = MotionSensor_isThereMotion(left);
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

void *threadCamera(void *arg)
{
    capture_init();
    while(1)
    {
        while(!Button_read(BUTTON_pathValue))
        {
            sleepForMs(10);
            continue;
        }
        camera_capture();
        capture_end();
    }
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
