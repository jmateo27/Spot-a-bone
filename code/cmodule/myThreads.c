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
        if (!cameraButton_read()){ // button is pressed
            // Tell the camera to take photos
            Comm_commandCamera();
            msleep(5000);
        }
    }
    return NULL;
}

void *threadPollNames(void *arg){
    char nameBuff[24]; // max length of name is 24
    while (1){
        if (Comm_getUserName(nameBuff)){
            Comm_sendUserName(nameBuff);
            printf("%s found\n", nameBuff);
            msleep(2000);
            memset(nameBuff, '\0', strlen(nameBuff));
        }
        msleep(50);
    }
}