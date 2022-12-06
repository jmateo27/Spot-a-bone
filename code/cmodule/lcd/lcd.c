/* 16x2 LCD Initialization C Sample Code */
/* Use freely to test wiring and derive your own LCD code. */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include "includes/gpio.h"
#define NUM_CHARS_ON_DISPLAY 18
#define SONGS_DIR "/mnt/remote/myApps/spotabone/comms/song.txt"

// nanosleep wrapper function - accepts seconds and nanoseconds to construct delay
static void delayFor(int, int);
// Flash the E pin high to low to have the LCD consume the data
static void pulseEnable();
// Write 4 bits to their corresponding pin (D4, D5, D6, D7)
static void write4Bits(uint8_t);
// Write a char to the LCD
static void writeChar(char);
// Write a message to the LCD
static void writeMessage(char *message);
// Initialize the LCD
static void LcdDisplay_init();
// Cleanup the LCD
static void LcdDisplay_cleanUp();
// Helper for clean up
static void clearDisplay();

static void scrollText();

static char msg[50];
static int messageLength = 0;

int main()
{
    char newMsg[50];
    newMsg[0] = '\0';
    FILE *ptr;
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
            scrollText();
        for (int i = 0; msg[i] != '\0'; i++)
        {
            msg[i] = '\0';
        }

        clearDisplay();

    }

    free(newMsg);
    char *buff;
    size_t sizeAllocated = 0;
    printf("\nPRESS RETURN TO EXIT \n");
    fflush(stdout);
    getline(&buff, &sizeAllocated, stdin);

    if (*buff == '\n')
    {
        LcdDisplay_cleanUp();
    }

    return 0;
}

static void LcdDisplay_init()
{
    // Set every GPIO pin to OUTPUT
    GPIO_writeDirection(RS_GPIO_NUMBER, "out");
    GPIO_writeDirection(E_GPIO_NUMBER, "out");
    GPIO_writeDirection(D4_GPIO_NUMBER, "out");
    GPIO_writeDirection(D5_GPIO_NUMBER, "out");
    GPIO_writeDirection(D6_GPIO_NUMBER, "out");
    GPIO_writeDirection(D7_GPIO_NUMBER, "out");

    // Set every data pin to 0
    GPIO_writeValue(E_GPIO_NUMBER, "0");
    GPIO_writeValue(D4_GPIO_NUMBER, "0");
    GPIO_writeValue(D5_GPIO_NUMBER, "0");
    GPIO_writeValue(D6_GPIO_NUMBER, "0");
    GPIO_writeValue(D7_GPIO_NUMBER, "0");

    printf("Configured pins...\n");

    // Set to command mode
    GPIO_writeValue(RS_GPIO_NUMBER, "0");

    // Special Function Set 1.
    write4Bits(0x03);     // 0011
    delayFor(0, 5000000); // 5 ms

    // Special Function Set 2.
    write4Bits(0x03);    // 0011
    delayFor(0, 128000); // 128 us

    // Special Function Set 3.
    write4Bits(0x03);    // 0011
    delayFor(0, 128000); // 128 us

    // Sets to 4-bit operation.
    write4Bits(0x2);      /* 0010 */
    delayFor(0, 1000000); // 1 ms

    // Sets to 4-bit operation. Sets 2-line display. Selects 5x8 dot character font.
    write4Bits(0x2);     /* 0010 - We can alternatively write 0000 here for 8-bit operation. */
    write4Bits(0x8);     /* 1000 - We can alternatively write 1100 here for 5x10 dot font. */
    delayFor(0, 128000); // 128 us

    // Display ON/OFF control.
    write4Bits(0x0);     /* 0000 */
    write4Bits(0x8);     /* 1000 */
    delayFor(0, 128000); // 128 us

    // Clear the display.
    write4Bits(0x0);    /* 0000 */
    write4Bits(0x1);    /* 0001 */
    delayFor(0, 64000); // 64 us

    // Sets mode to increment cursor position by 1 and shift right when writing to display.
    write4Bits(0x0);     /* 0000 */
    write4Bits(0x6);     /* 0110 */
    delayFor(0, 128000); // 128 us

    // Turns on display. This corresponds to the instruction 0000 1100 in binary.
    // To be able to see the cursor, use 0000 1110.
    // To enable cursor blinking, use 0000 1111.
    write4Bits(0x0);    /* 0000 */
    write4Bits(0xF);    /* 1111 */
    delayFor(0, 64000); // 64 us

    printf("Completed initialization.\n");

    // Pull RS up to write data.
    GPIO_writeValue(RS_GPIO_NUMBER, "1");
}

void LcdDisplay_cleanUp()
{

    clearDisplay();
    printf("Completed clean up.\n");
}

void clearDisplay()
{
    // Set to command mode
    GPIO_writeValue(RS_GPIO_NUMBER, "0");

    // Special Function Set 1.
    write4Bits(0x03);     // 0011
    delayFor(0, 5000000); // 5 ms

    // Special Function Set 2.
    write4Bits(0x03);    // 0011
    delayFor(0, 128000); // 128 us

    // Special Function Set 3.
    write4Bits(0x03);    // 0011
    delayFor(0, 128000); // 128 us

    // Sets to 4-bit operation.
    write4Bits(0x2);      /* 0010 */
    delayFor(0, 1000000); // 1 ms

    // Sets to 4-bit operation. Sets 2-line display. Selects 5x8 dot character font.
    write4Bits(0x2);     /* 0010 - We can alternatively write 0000 here for 8-bit operation. */
    write4Bits(0x8);     /* 1000 - We can alternatively write 1100 here for 5x10 dot font. */
    delayFor(0, 128000); // 128 us

    // Display ON/OFF control.
    write4Bits(0x0);     /* 0000 */
    write4Bits(0x8);     /* 1000 */
    delayFor(0, 128000); // 128 us

    // Clear the display.
    write4Bits(0x0);    /* 0000 */
    write4Bits(0x1);    /* 0001 */
    delayFor(0, 64000); // 64 us

    // Sets mode to increment cursor position by 1 and shift right when writing to display.
    write4Bits(0x0);     /* 0000 */
    write4Bits(0x6);     /* 0110 */
    delayFor(0, 128000); // 128 us

    // Turns on display. This corresponds to the instruction 0000 1100 in binary.
    // To be able to see the cursor, use 0000 1110.
    // To enable cursor blinking, use 0000 1111.
    write4Bits(0x0);    /* 0000 */
    write4Bits(0xF);    /* 1111 */
    delayFor(0, 64000); // 64 us

    // Pull RS up to write data.
    GPIO_writeValue(RS_GPIO_NUMBER, "1");

    return;
}

void scrollText()
{
    int j = 0;
    int h;
    char scrollPadding[] = "                ";
    int printLength;
    printLength = strlen(scrollPadding) + messageLength;
    for (int n = 0; n < printLength; n++)
    {
        h = 16;

        // REPLACE WITH JUSTIN'S SLEEP FUNTION

        delayFor(0, 100000000);

        // REPLACE WITH JUSTIN'S SLEEP FUNTION

        if (j > printLength)
            j = 0;
        for (int i = 0; i <= j; i++)
        {
            scrollPadding[h - j] = msg[i]; // scrollpadding[16 - 0] = msg[ i = 0 ]
            h++;
        }
        // lcdPosition(lcd, 0, 0);
        clearDisplay();
        writeMessage(scrollPadding);
        j++;
    }
}

void writeMessage(char *message)
{
    printf("Writing \"%s\" to LCD...\n", message);
    for (int i = 0; i < strlen(message); i++)
    {
        writeChar(message[i]);
    }
}

void writeChar(char c)
{
    unsigned int upper_bits = (c >> 4);
    unsigned int lower_bits = c & 0xF;
    write4Bits(upper_bits);
    write4Bits(lower_bits);
}

static void pulseEnable()
{
    struct timespec pulseDelay = {0, 1000000};
    GPIO_writeValue(E_GPIO_NUMBER, "1");
    nanosleep(&pulseDelay, (struct timespec *)NULL);
    GPIO_writeValue(E_GPIO_NUMBER, "0");
    nanosleep(&pulseDelay, (struct timespec *)NULL);
}

static void write4Bits(uint8_t value)
{
    char strBit[2];
    strBit[1] = '\0';
    strBit[0] = (value & 0x01 ? 1 : 0) + '0';
    GPIO_writeValue(D4_GPIO_NUMBER, strBit);

    strBit[0] = ((value >> 1) & 0x01 ? 1 : 0) + '0';
    GPIO_writeValue(D5_GPIO_NUMBER, strBit);

    strBit[0] = ((value >> 2) & 0x01 ? 1 : 0) + '0';
    GPIO_writeValue(D6_GPIO_NUMBER, strBit);

    strBit[0] = ((value >> 3) & 0x01 ? 1 : 0) + '0';
    GPIO_writeValue(D7_GPIO_NUMBER, strBit);

    pulseEnable();
}

static void delayFor(int s, int ns)
{
    struct timespec delay = {s, ns};
    nanosleep(&delay, (struct timespec *)NULL);
}