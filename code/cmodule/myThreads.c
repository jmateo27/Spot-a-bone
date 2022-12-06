#include "includes/myThreads.h"

#define oneMin 1

void *threadNFC(void *arg)
{
    NFC_descriptor *descPtr = (NFC_descriptor *)arg;
    int tagNum = 0, prevTagNum = 0;
    while (1)
    {
        NFC_init(descPtr);

        if ((tagNum = NFC_poll(descPtr)) != prevTagNum && tagNum != 0)
        {
            printf("Found tag #%d\n", tagNum);
            if (tagNum != 0)
                prevTagNum = tagNum;
            Comm_queueUpSong(tagNum);
        }

        NFC_cleanup(descPtr);
    }
    return NULL;
}

void *threadCameraButton(void *arg){
    while (1){
        if (!cameraButton_read()){ // button is pressed
            // Tell the camera to take photos
            Comm_commandCamera();
            msleep(5000);
        }
    }
    return NULL;
}