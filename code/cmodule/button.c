#include "includes/button.h"
#include <stdio.h>

void endButton_init()
{
    runCommand("config-pin p8.43 gpio"); // force the button's pin to be treated as GPIO
    writeToFile(ENDBUTTON_pathDirection, "in");
    writeToFile(ENDBUTTON_pathactiveLow, "1");
}

// Implementation partially inspired from assignment document (Brian Fraser)
int endButton_read()
{
    char *fileName = ENDBUTTON_pathValue;
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL)
    {
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }
    // Read string (line)
    char result[MAX_LENGTH];
    fgets(result, MAX_LENGTH, pFile);
    // Close
    fclose(pFile);
    if (result[0] == '1')
        return 1;
    else
        return 0;
}