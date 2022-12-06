#include "includes/communication.h"

int maxTagTens = 2;

typedef int FD;

typedef enum commFiles_e commFiles;
enum commFiles_e{
    commandCamera,
    userName,
    commandSpotify,
    songName
};

char *commFile[] = {
    "/mnt/remote/myApps/spotabone/comms/takePhotos.txt",
    "/mnt/remote/myApps/spotabone/comms/name.txt",
    "/mnt/remote/myApps/spotabone/comms/NFC.txt",
    "/mnt/remote/myApps/spotabone/comms/song.txt"
};

void Comm_queueUpSong(int tagNum)
{
	FILE *pFile;
	while ((pFile = fopen(commFile[commandSpotify], "ab")) == NULL); // Wait if cannot open... (somewhat like a mutex)

	char toWrite[maxTagTens];
	sprintf(toWrite, "s%d\n", tagNum);
	fprintf(pFile, toWrite);

	fclose(pFile);
	return;
}

void Comm_commandCamera(){
	FILE *pFile;
	while ((pFile = fopen(commFile[commandCamera], "ab")) == NULL); // Wait if cannot open... (somewhat like a mutex)

	char toWrite[maxTagTens];
	sprintf(toWrite, "s%d\n", 1);
	fprintf(pFile, toWrite);

	fclose(pFile);
	return;
}

bool Comm_getUserName(char *name){
    char *fileName = commFile[userName];
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
    char *filename = commFile[songName];
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