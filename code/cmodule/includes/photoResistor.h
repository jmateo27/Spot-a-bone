#ifndef _PHOTORESISTOR_H_
#define _PHOTORESISTOR_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include "timing.h"

#define A2D_FILE_VOLTAGE33 "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define A2D_FILE_VOLTAGE35 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define A2D_FILE_VOLTAGE37 "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING 4095.0
#define MAX_SAMPLE_SIZE 1200

typedef struct Sample PHOTORES_sample;
struct Sample{
    float A2DReading;
    clock_t time;
    long double timeInterval;
};

typedef struct SampleResult PHOTORES_sampleResult;
struct SampleResult{
    int numberOfSamples;
    int numberOfDips;
};

typedef struct Record PHOTORES_record;
struct Record{
    clock_t startTime;
    float maxSample;
    float minSample;
    long double maxInterval;
    long double minInterval;
    float averageReading;
};
//PIN 33
int read_LEFT();

//PIN 35
int read_RIGHT();

//PIN 37
int read_MIDDLE();

//PIN 33
void PHOTORES_LEFT(PHOTORES_sample *sample, PHOTORES_record *allTimeRecord, PHOTORES_sampleResult *res, clock_t *prevTimeStamp);

//PIN 35
void PHOTORES_RIGHT(PHOTORES_sample *sample, PHOTORES_record *allTimeRecord, PHOTORES_sampleResult *res, clock_t *prevTimeStamp);

//PIN 37
void PHOTORES_MIDDLE(PHOTORES_sample *sample, PHOTORES_record *allTimeRecord, PHOTORES_sampleResult *res, clock_t *prevTimeStamp);

float PHOTORES_exponentialAverage(float *prevAverageReading, PHOTORES_sample *sample, int size);

float PHOTORES_averageReading(PHOTORES_sample *data, int size);

#endif