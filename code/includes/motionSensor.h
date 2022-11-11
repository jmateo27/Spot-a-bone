#ifndef MOTIONSENSOR_H_
#define MOTIONSENSOR_H_

#include <stdio.h>
#include <stdlib.h>

void motionSensor_initiate();

int motionSensor_isThereMotion();

void motionSensor_writeToFile(char *fileName, char *toWrite);

void motionSensor_runCommand(char *command);

#endif