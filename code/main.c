#include "includes/nfcReader.h"
#include "includes/myThreads.h"
#include "includes/button.h"

int main()
{
    pthread_t nfc_t;
    // pthread_t motionSensor_t;
    NFC_descriptor nfc_desc;
    Button_init();

    if (pthread_create(&nfc_t, NULL, &threadNFC, &nfc_desc) < 0)
    {
        perror("Could not create NFC thread\n");
        return 1;
    }

    // if (pthread_create(&motionSensor_t, NULL, &threadMotionSensor, NULL) < 0)
    // {
    //     perror("Could not create motion sensor thread\n");
    //     return 1;
    // }

    while (!Button_read(BUTTON_pathValue));
    pthread_cancel(nfc_t);
    // pthread_cancel(motionSensor_t);
    NFC_cleanup(&nfc_desc);
    printf("Ending... Goodbye!\n");
    return 0;
}
