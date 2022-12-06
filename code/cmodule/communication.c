#include "includes/communication.h"

typedef int FD;

char **commFiles = {
    "/mnt/remote/myApps/spotabone/comms/takePhotos.txt",
    "/mnt/remote/myApps/spotabone/comms/name.txt",
    "/mnt/remote/myApps/spotabone/comms/NFC.txt",
    "/mnt/remote/myApps/spotabone/comms/song.txt"
};

void Comm_queueUpSong(int tagNum)
{
	FILE *pFile;
	while ((pFile = fopen(commFiles[commandSpotify], "ab")) == NULL); // Wait if cannot open... (somewhat like a mutex)

	char toWrite[maxTagTens];
	sprintf(toWrite, "s%d\n", tagNum);
	fprintf(pFile, toWrite);

	fclose(pFile);
}

void Comm_commandCamera(){
	FILE *pFile;
	while ((pFile = fopen(commFiles[commandCamera], "ab")) == NULL); // Wait if cannot open... (somewhat like a mutex)

	char toWrite[maxTagTens];
	sprintf(toWrite, "s%d\n", 1);
	fprintf(pFile, toWrite);

	fclose(pFile);
}

bool Comm_getUserName(char *name){
    char *fileName = commFiles[userName];
	FD pFile = open(fileName, O_RDWR);
	if (!pFile)
	{
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		exit(-1);
	}

	// Read string (line)
	ssize_t count;
	count = read(pFile, name, 16);
	// Close
	// fclose(pFile);
	fclose(fopen(fileName, "w")); // Clear the file
	if (count > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Comm_getSongName(char *song){
    char *filename = commFiles[songName];
	FD pFile = open(filename, O_RDWR);
	if (!pFile)
	{
		printf("ERROR: Unable to open file (%s) for read\n", filename);
		exit(-1);
	}

	// Read string (line)
	ssize_t count;
	count = read(pFile, song, 16);
	// Close
	// fclose(pFile);
	fclose(fopen(filename, "w")); // Clear the file
	if (count > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}