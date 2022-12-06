#include "includes/myThreads.h"

#define oneMin 1

void *threadNFC(void *arg)
{
    NFC_descriptor *descPtr = (NFC_descriptor *)arg;
    tag tagNum, prevTagNum = {0, false};
    NFC_init(descPtr);
    char s = 's';
    while (1)
    {
        NFC_poll(descPtr, &tagNum);
        if (!(tagNum.tagNum == prevTagNum.tagNum && tagNum.isSong == prevTagNum.isSong) && tagNum != nullTag)
        {   
            if (tagNum.isSong){
                s = 's';
            }
            else{
                s = 'p';
            }
            printf("Found tag %c%d\n", s, tagNum.tagNum);
            if (tagNum.tagNum != 0)
                prevTagNum = tagNum;
            Comm_queueUpSong(tagNum.tagNum, s);
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
    FILE * ptr;
    newMsg[0] = '\0';
    LcdDisplay_init();
    while (1)
    {
        while (!newMsg[0])
        {
            delayFor(1, 0);
            ptr = fopen(SONGS_DIR, "r");
            if (ptr == NULL)
            {
                exit(1);
            }
            fscanf(ptr, "%[^\n]s", newMsg);

            fclose(ptr);
        }

        fclose(fopen(SONGS_DIR, "w"));

        messageLength = 0;
        for (int i = 0; newMsg[i] != '\0'; i++)
        {
            msg[i] = newMsg[i];
            messageLength++;
        }
        newMsg[0] = '\0';
        for (int i = 0; i < 2; i++)
            scrollText(msg,messageLength);
        
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