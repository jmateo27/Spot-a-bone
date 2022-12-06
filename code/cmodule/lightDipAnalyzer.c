#include "includes/lightDipAnalyzer.h"

static PHOTORES_sample PHOTORES_buffer[MAX_SAMPLE_SIZE];
static PHOTORES_record PHOTORES_allTimeRecord;
static pthread_mutex_t recordMutex = PTHREAD_MUTEX_INITIALIZER;
static PHOTORES_sampleResult res;
static pthread_mutex_t resMutex = PTHREAD_MUTEX_INITIALIZER;


void *readLeft(void *args){
    PHOTORES_record recordBuffer;
    PHOTORES_sampleResult resBuffer;
    clock_t dummyTime = clock() - 100 * CLOCKS_PER_SEC/1000;
    bool first = true;

    while(1){ //put mutex here
        pthread_mutex_lock(&recordMutex);
        recordBuffer.averageReading = PHOTORES_allTimeRecord.averageReading;
        recordBuffer.maxInterval = PHOTORES_allTimeRecord.maxInterval;
        recordBuffer.maxSample = PHOTORES_allTimeRecord.maxSample;
        recordBuffer.minInterval = PHOTORES_allTimeRecord.minInterval;
        recordBuffer.minSample = PHOTORES_allTimeRecord.minSample;
        recordBuffer.startTime = PHOTORES_allTimeRecord.startTime;
        pthread_mutex_unlock(&recordMutex);

        PHOTORES_LEFT(PHOTORES_buffer, &recordBuffer, &resBuffer, &dummyTime);

        pthread_mutex_lock(&resMutex);
        res.numberOfDips = resBuffer.numberOfDips;
        res.numberOfSamples = resBuffer.numberOfSamples;
        pthread_mutex_unlock(&resMutex);

        if(!first)
            recordBuffer.averageReading = PHOTORES_exponentialAverage(&(recordBuffer.averageReading), PHOTORES_buffer, resBuffer.numberOfSamples);
        else{
            recordBuffer.averageReading = PHOTORES_averageReading(PHOTORES_buffer, resBuffer.numberOfSamples);
            first = false;
        }
        if(resBuffer.numberOfDips > 0)
            leftDip();

        // printf("LEFT: # Dips: %d     # Sample: %d\n",
        //     resBuffer.numberOfDips, resBuffer.numberOfSamples);

        pthread_mutex_lock(&recordMutex);
        PHOTORES_allTimeRecord.averageReading = recordBuffer.averageReading;
        PHOTORES_allTimeRecord.maxInterval = recordBuffer.maxInterval;
        PHOTORES_allTimeRecord.maxSample = recordBuffer.maxSample;
        PHOTORES_allTimeRecord.minInterval = recordBuffer.minInterval;
        PHOTORES_allTimeRecord.minSample = recordBuffer.minSample;
        PHOTORES_allTimeRecord.startTime = recordBuffer.startTime;
        pthread_mutex_unlock(&recordMutex);
    }
    return NULL;
}

void *readRight(void *args){
    PHOTORES_record recordBuffer;
    PHOTORES_sampleResult resBuffer;
    clock_t dummyTime = clock() - 100 * CLOCKS_PER_SEC/1000;
    bool first = true;

    while(1){ //put mutex here
        pthread_mutex_lock(&recordMutex);
        recordBuffer.averageReading = PHOTORES_allTimeRecord.averageReading;
        recordBuffer.maxInterval = PHOTORES_allTimeRecord.maxInterval;
        recordBuffer.maxSample = PHOTORES_allTimeRecord.maxSample;
        recordBuffer.minInterval = PHOTORES_allTimeRecord.minInterval;
        recordBuffer.minSample = PHOTORES_allTimeRecord.minSample;
        recordBuffer.startTime = PHOTORES_allTimeRecord.startTime;
        pthread_mutex_unlock(&recordMutex);

        PHOTORES_RIGHT(PHOTORES_buffer, &recordBuffer, &resBuffer, &dummyTime);

        pthread_mutex_lock(&resMutex);
        res.numberOfDips = resBuffer.numberOfDips;
        res.numberOfSamples = resBuffer.numberOfSamples;
        pthread_mutex_unlock(&resMutex);

        if(!first)
            recordBuffer.averageReading = PHOTORES_exponentialAverage(&(recordBuffer.averageReading), PHOTORES_buffer, resBuffer.numberOfSamples);
        else{
            recordBuffer.averageReading = PHOTORES_averageReading(PHOTORES_buffer, resBuffer.numberOfSamples);
            first = false;
        }

        if(resBuffer.numberOfDips > 0)
            rightDip();

        // printf("RIGHT: # Dips: %d     # Sample: %d\n",
        //     resBuffer.numberOfDips, resBuffer.numberOfSamples);

        pthread_mutex_lock(&recordMutex);
        PHOTORES_allTimeRecord.averageReading = recordBuffer.averageReading;
        PHOTORES_allTimeRecord.maxInterval = recordBuffer.maxInterval;
        PHOTORES_allTimeRecord.maxSample = recordBuffer.maxSample;
        PHOTORES_allTimeRecord.minInterval = recordBuffer.minInterval;
        PHOTORES_allTimeRecord.minSample = recordBuffer.minSample;
        PHOTORES_allTimeRecord.startTime = recordBuffer.startTime;
        pthread_mutex_unlock(&recordMutex);
    }
    return NULL;
}

void *readMIDDLE(void *args){
    PHOTORES_record recordBuffer;
    PHOTORES_sampleResult resBuffer;
    clock_t dummyTime = clock() - 100 * CLOCKS_PER_SEC/1000;
    bool first = true;

    while(1){ //put mutex here
        pthread_mutex_lock(&recordMutex);
        recordBuffer.averageReading = PHOTORES_allTimeRecord.averageReading;
        recordBuffer.maxInterval = PHOTORES_allTimeRecord.maxInterval;
        recordBuffer.maxSample = PHOTORES_allTimeRecord.maxSample;
        recordBuffer.minInterval = PHOTORES_allTimeRecord.minInterval;
        recordBuffer.minSample = PHOTORES_allTimeRecord.minSample;
        recordBuffer.startTime = PHOTORES_allTimeRecord.startTime;
        pthread_mutex_unlock(&recordMutex);

        PHOTORES_MIDDLE(PHOTORES_buffer, &recordBuffer, &resBuffer, &dummyTime);

        pthread_mutex_lock(&resMutex);
        res.numberOfDips = resBuffer.numberOfDips;
        res.numberOfSamples = resBuffer.numberOfSamples;
        pthread_mutex_unlock(&resMutex);

        if(!first)
            recordBuffer.averageReading = PHOTORES_exponentialAverage(&(recordBuffer.averageReading), PHOTORES_buffer, resBuffer.numberOfSamples);
        else{
            recordBuffer.averageReading = PHOTORES_averageReading(PHOTORES_buffer, resBuffer.numberOfSamples);
            first = false;
        }
        
        if(resBuffer.numberOfDips > 0)
            middleDip();
        

        // printf("MIDDLE: # Dips: %d     # Sample: %d\n",
        //         resBuffer.numberOfDips, resBuffer.numberOfSamples);

        pthread_mutex_lock(&recordMutex);
        PHOTORES_allTimeRecord.averageReading = recordBuffer.averageReading;
        PHOTORES_allTimeRecord.maxInterval = recordBuffer.maxInterval;
        PHOTORES_allTimeRecord.maxSample = recordBuffer.maxSample;
        PHOTORES_allTimeRecord.minInterval = recordBuffer.minInterval;
        PHOTORES_allTimeRecord.minSample = recordBuffer.minSample;
        PHOTORES_allTimeRecord.startTime = recordBuffer.startTime;
        pthread_mutex_unlock(&recordMutex);
    }
    return NULL;
}
void startMotionSensorThreads(){
    pthread_t lightLEFT, lightRIGHT, lightMIDDLE;
    res.numberOfDips = 0;
    res.numberOfSamples = 0;

    PHOTORES_allTimeRecord.maxInterval = 0;
    PHOTORES_allTimeRecord.minInterval = 999927;
    PHOTORES_allTimeRecord.maxSample = 0;
    PHOTORES_allTimeRecord.minSample = 999927;
    motionStart();
    if (pthread_create(&lightLEFT, NULL, &readLeft, NULL) < 0){
        perror("Could not create lightSensor1 thread\n");
        return;
    }
    if (pthread_create(&lightRIGHT, NULL, &readRight, NULL) < 0){
        perror("Could not create lightSensor2 thread\n");
        return;
    }
    if (pthread_create(&lightMIDDLE, NULL, &readMIDDLE, NULL) < 0){
        perror("Could not create lightSensor3 thread\n");
        return;
    }

    return;
}

void lightDipEnd(){
    motionStop();
    pthread_cancel(lightLEFT);
    pthread_cancel(lightRIGHT);
    pthread_cancel(lightMIDDLE);
}
