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

void *threadLCDScreen(void *args)
{
    char msg[50];
    char newMsg[50];
    int messageLength = 0;

    newMsg[0] = '\0';
    LcdDisplay_init();
    while (1)
    {
        while (!Comm_getSongName(newMsg)){
            msleep(200);
        }

        printf("%s\n",newMsg);            
        messageLength = 0;
        for (int i = 0; newMsg[i] != '\0'; i++)
        {
            msg[i] = newMsg[i];
            messageLength++;
        }
        newMsg[0] = '\0';
        for (int i = 0; i < 2; i++)
            scrollText(msg, messageLength);
        for (int i = 0; msg[i] != '\0'; i++)
        {
            msg[i] = '\0';
        }

        clearDisplay();

    }

    char *buff;
    size_t sizeAllocated = 0;
    printf("\nPRESS RETURN TO EXIT \n");
    fflush(stdout);
    getline(&buff, &sizeAllocated, stdin);

    if (*buff == '\n')
    {
        LcdDisplay_cleanUp();
    }

    return NULL;
}