#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum commFiles_e commFiles;
enum commFiles_e{
    commandCamera,
    userName,
    commandSpotify,
    songName
};

void Comm_queueUpSong(int tagNum);
void Comm_commandCamera();
bool Comm_getUserName(char *name);
bool Comm_getSongName(char *song);

#endif