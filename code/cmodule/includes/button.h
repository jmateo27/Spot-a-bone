#ifndef BUTTON_H_
#define BUTTON_H_
// Needed for exit() and etc.
#include <stdlib.h>
#include "common.h"

// Paths of end button characteristics that need to be set
#define ENDBUTTON_pathValue "/sys/class/gpio/gpio72/value"
#define ENDBUTTON_pathactiveLow "/sys/class/gpio/gpio72/active_low"
#define ENDBUTTON_pathDirection "/sys/class/gpio/gpio72/direction"

#define CAMERABUTTON_pathValue "/sys/class/gpio/gpio30/value"
#define CAMERABUTTON_pathactiveLow "/sys/class/gpio/gpio30/active_low"
#define CAMERABUTTON_pathDirection "/sys/class/gpio/gpio30/direction"

static const int MAX_LENGTH = 1024;

void endButton_init();
void cameraButton_init();

int endButton_read();
int cameraButton_read();

#endif