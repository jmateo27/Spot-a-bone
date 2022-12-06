#include "includes/nfcReader.h"
#include "includes/myThreads.h"
#include "includes/button.h"


/*
cd /sys/class/gpio
sudo echo 48 > export
sudo echo 51 > export
config-pin P9_15 gpio
config-pin P9_16 gpio
config-pin P9_17 i2c
config-pin P9_18 i2c
*/

int main()
{
    pthread_t nfc_t, cameraButton_t;
    // pthread_t motionSensor_t;
    NFC_descriptor nfc_desc;
    endButton_init();
    cameraButton_init();

    if (pthread_create(&nfc_t, NULL, &threadNFC, &nfc_desc) < 0)
    {
        perror("Could not create NFC thread\n");
        return 1;
    }

    if (pthread_create(&cameraButton_t, NULL, &threadCameraButton, NULL) < 0)
    {
        perror("Could not create Camera button thread\n");
        return 1;
    }

    while (!endButton_read());

    pthread_cancel(nfc_t);
    pthread_cancel(cameraButton_t);
    NFC_cleanup(&nfc_desc);
    printf("Ending... Goodbye!\n");
    return 0;
}
