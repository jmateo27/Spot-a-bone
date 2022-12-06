#include "includes/musicControl.h"
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>

#define MS_BUFFER 50

bool callClose = true;
bool leftSide = false;
bool rightSide = false;
bool middleSide = false;
bool leftFirst = false;
bool rightFirst = false;
bool breakOutRight = false;
bool breakOutLeft = false;
bool isPaused = false;
pthread_t leftPthread, rightPthread, middlePthread;

void leftDip(){
    leftSide = true;
    return;
}

void rightDip(){
    rightSide = true;
    return;
}

void middleDip(){
    middleSide = true;
    return;
}

void swipeLeft(){
    rightSide = false;
    leftSide = false;
    rightFirst = false;
    leftFirst = false;
    breakOutRight = true;
    breakOutLeft = true;
    Comm_sendUserName("track");
    printf("swipe to the left\n");
    return;
}

void swipeRight(){
    rightSide = false;
    leftSide = false;
    leftFirst = false;
    rightFirst = false;
    breakOutRight = true;
    breakOutLeft = true;
    Comm_sendUserName("skip");
    printf("swipe to the right\n");
    return;
}

void* timeLeft(){
    while(callClose){
        if(leftSide){
            if(!rightFirst)
                leftFirst = true;
            clock_t end_time;
            end_time = clock() + MS_BUFFER * CLOCKS_PER_SEC/1000;
            while (clock() < end_time) {
                if(rightSide){
                    if(leftFirst){
                        swipeRight();
                    }
                    if(breakOutLeft){
                        break;
                    }
                }
            }
        }
        breakOutLeft = false;
        leftFirst = false;
    }
    return NULL;
}

void* timeRight(){
    while(callClose){
        if(rightSide){
            if(!leftFirst)
                rightFirst = true;
            clock_t end_time;
            end_time = clock() + MS_BUFFER * CLOCKS_PER_SEC/1000;
            while (clock() < end_time) {
                if(leftSide){
                    if(rightFirst){
                        swipeLeft();
                    }
                    if(breakOutRight){
                        break;
                    }
                }
            }
        }
        breakOutRight = false;
        rightFirst = false;
    }
    return NULL;
}

void* timeMiddle(){
    while(callClose){
        if(middleSide){
            if (!isPaused){
                Comm_sendUserName("pause");
            }
            else{
                Comm_sendUserName("play");
            }
            isPaused = !isPaused;
            printf("PAUSE/PLAY\n");
            middleSide = false;
        }
    }
    return NULL;
}

void motionStart(){
    if (pthread_create(&leftPthread, NULL, &timeLeft, NULL) < 0){
        perror("Could not create leftSensor thread\n");
        return;
    }
    if (pthread_create(&rightPthread, NULL, &timeRight, NULL) < 0){
        perror("Could not create leftSensor thread\n");
        return;
    }
    if (pthread_create(&middlePthread, NULL, &timeMiddle, NULL) < 0){
        perror("Could not create middleSensor thread\n");
        return;
    }
    return;
}

void motionStop(){
    callClose = false;
    pthread_join(leftPthread, NULL);
    pthread_join(rightPthread, NULL);
    pthread_join(middlePthread, NULL);
    return;
}