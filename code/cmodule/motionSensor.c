#include "includes/motionSensor.h"

typedef struct
{
    char *value;
    char *activeLow;
    char *direction;
} Paths;

Paths MotionSensorPath[numSides] = {
    {"/sys/class/gpio/gpio66/value",
     "/sys/class/gpio/gpio66/active_low",
     "/sys/class/gpio/gpio66/direction"},

    {"/sys/class/gpio/gpio67/value",
     "/sys/class/gpio/gpio67/active_low",
     "/sys/class/gpio/gpio67/direction"}};

void MotionSensor_init(Side side)
{
    Paths p = MotionSensorPath[side];
    writeToFile(p.direction, "in");
    writeToFile(p.activeLow, "0");
}

int MotionSensor_isThereMotion(Side side)
{
    FILE *pFile = fopen(MotionSensorPath[side].value, "r");
    if (pFile == NULL)
    {
        printf("ERROR: Unable to open file (%s) for read\n", MotionSensorPath[side].value);
        exit(-1);
    }
    // Read string (line)
    int maxlen = 16;
    char result[maxlen];
    fgets(result, maxlen, pFile);
    // Close
    fclose(pFile);
    if (result[0] == '1')
        return 1;
    else
        return 0;
}