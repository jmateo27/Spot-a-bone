#include "includes/motionSensor.h"

#define motionSensor_pathValue "/sys/class/gpio/gpio27/value"
#define motionSensor_pathactiveLow "/sys/class/gpio/gpio27/active_low"
#define motionSensor_pathDirection "/sys/class/gpio/gpio27/direction"
#define MAX_LENGTH 16
void motionSensor_initiate(){
	motionSensor_runCommand("config-pin P9.17 gpio");
	motionSensor_writeToFile(motionSensor_pathDirection, "in");
    motionSensor_writeToFile(motionSensor_pathactiveLow, "0");
}

int motionSensor_isThereMotion(){
    FILE *pFile = fopen(motionSensor_pathValue, "r");
    if (pFile == NULL) {
        printf("ERROR: Unable to open file (%s) for read\n", motionSensor_pathValue);
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

void motionSensor_writeToFile(char *fileName, char *toWrite){
    FILE *pFile = fopen(fileName, "w");
    if (pFile == NULL) {
        printf("ERROR: Unable to open export file.\n");
        exit(1);
    }

    fprintf(pFile, toWrite);

    fclose(pFile);
}

void motionSensor_runCommand(char *command)
{
	// Execute the shell command (output into pipe)
	FILE *pipe = popen(command, "r");
	// Ignore output of the command; but consume it
	// so we don't get an error when closing the pipe.
	char buffer[1024];
	while (!feof(pipe) && !ferror(pipe))
	{
		if (fgets(buffer, sizeof(buffer), pipe) == NULL)
			break;
		// printf("--> %s", buffer); // Uncomment for debugging
	}
	// Get the exit code from the pipe; non-zero is an error:
	int exitCode = WEXITSTATUS(pclose(pipe));
	if (exitCode != 0)
	{
		perror("Unable to execute command:");
		printf(" command: %s\n", command);
		printf(" exit code: %d\n", exitCode);
	}
}