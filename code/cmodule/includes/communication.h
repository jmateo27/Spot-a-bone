#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

void Comm_queueUpSong(int tagNum);
void Comm_commandCamera();
bool Comm_getUserName(char *name);
bool Comm_getSongName(char *song);

#endif