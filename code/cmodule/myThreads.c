#include "includes/myThreads.h"

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
            Comm_queueUpSong(tagNum);
            msleep(50);
        }
    }
    return NULL;
}

void *threadCameraButton(void *arg){
    while (1){
        if (cameraButton_read()){ // button is pressed
            // Tell the camera to take photos
            Comm_commandCamera();
            printf("commanding camera\n");
            msleep(10000);
        }
    }
    return NULL;
}