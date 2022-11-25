#include "includes/button.h"
#include <stdio.h>

void Button_init(){
    runCommand("config-pin p8.43 gpio"); //force the button's pin to be treated as GPIO
    writeToFile(BUTTON_pathDirection, "in");
    writeToFile(BUTTON_pathactiveLow, "1");
}

// Implementation partially inspired from assignment document (Brian Fraser)
int Button_read(char *fileName){
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) {
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