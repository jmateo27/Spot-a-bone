/* 16x2 LCD Initialization C Sample Code */
/* Use freely to test wiring and derive your own LCD code. */

#ifndef LCDSCREEN_H_
#define LCDSCREEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include "gpio.h"
#include "timing.h"

#define NUM_CHARS_ON_DISPLAY 18
#define SONGS_DIR "/mnt/remote/myApps/spotabone/comms/song.txt"

// Initialize the LCD
void LcdDisplay_init();
// Cleanup the LCD
void LcdDisplay_cleanUp();
// nanosleep wrapper function - accepts seconds and nanoseconds to construct delay
void delayFor(int, int);
// Flash the E pin high to low to have the LCD consume the data
void pulseEnable();
// Write 4 bits to their corresponding pin (D4, D5, D6, D7)
void write4Bits(uint8_t);
// Write a char to the LCD
void writeChar(char);
// Write a message to the LCD
void writeMessage(char *message);
// Helper for clean up
void clearDisplay();

void scrollText(char *msg);


#endif