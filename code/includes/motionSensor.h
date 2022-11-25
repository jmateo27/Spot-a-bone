// Uses specifically two motion sensors
// This makes it so that motion can be distinguished between
// left and right
#ifndef MOTIONSENSOR_H_
#define MOTIONSENSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef enum side_e Side;
enum side_e
{
    left,
    right,
    numSides
};

void MotionSensor_init(Side side);

int MotionSensor_isThereMotion(Side side);

void MotionSensor_writeToFile(char *fileName, char *toWrite);

void MotionSensor_runCommand(char *command);

#endif