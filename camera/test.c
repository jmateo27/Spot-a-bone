// #include "capture.h"
#include <stdio.h>
#include <stdlib.h>

void NFC_runCommand(char *command)
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

/*
sudo apt-get install libv4l-dev
sudo apt-get install v4l-utils
sudo apt-get install ffmpeg
*/

int main(){
    NFC_runCommand("./capture -F -c 300 -o > output.raw");
    NFC_runCommand("ffmpeg -f mjpeg -i output.raw -vcodec copy output.mp4");
    return 0;
}