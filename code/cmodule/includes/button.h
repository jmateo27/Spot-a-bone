#ifndef BUTTON_H_
#define BUTTON_H_
// Needed for exit() and etc.
#include <stdlib.h>
#include "common.h"

// Paths of end button characteristics that need to be set
#define ENDBUTTON_pathValue "/sys/class/gpio/gpio72/value"
#define ENDBUTTON_pathactiveLow "/sys/class/gpio/gpio72/active_low"
#define ENDBUTTON_pathDirection "/sys/class/gpio/gpio72/direction"

static const int MAX_LENGTH = 1024;

void endButton_init();

// Will return the integer form of the reading from fileName
int endButton_read();

#endif