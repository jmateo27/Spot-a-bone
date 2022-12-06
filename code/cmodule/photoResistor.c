#include "includes/photoResistor.h"


#define TOLERARANCEDIVISION 10
int read_LEFT(){
    // Open file
    FILE *f = fopen(A2D_FILE_VOLTAGE33, "r");
    if (!f) {
        printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
        printf(" Check /boot/uEnv.txt for correct options.\n");
        exit(-1);
    }
    // Get reading
    int a2dReading = 0;
    int itemsRead = fscanf(f, "%d", &a2dReading);
    if (itemsRead <= 0) {
        printf("ERROR: Unable to read values from voltage input file.\n");
        exit(-1);
    }
    // Close file
    fclose(f);
    return a2dReading;
}
int read_RIGHT(){
    // Open file
    FILE *f = fopen(A2D_FILE_VOLTAGE35, "r");
    if (!f) {
        printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
        printf(" Check /boot/uEnv.txt for correct options.\n");
        exit(-1);
    }
    // Get reading
    int a2dReading = 0;
    int itemsRead = fscanf(f, "%d", &a2dReading);
    if (itemsRead <= 0) {
        printf("ERROR: Unable to read values from voltage input file.\n");
        exit(-1);
    }
    // Close file
    fclose(f);
    return a2dReading;
}
int read_MIDDLE(){
    // Open file
    FILE *f = fopen(A2D_FILE_VOLTAGE37, "r");
    if (!f) {
        printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
        printf(" Check /boot/uEnv.txt for correct options.\n");
        exit(-1);
    }
    // Get reading
    int a2dReading = 0;
    int itemsRead = fscanf(f, "%d", &a2dReading);
    if (itemsRead <= 0) {
        printf("ERROR: Unable to read values from voltage input file.\n");
        exit(-1);
    }
    // Close file
    fclose(f);
    return a2dReading;
}

void PHOTORES_RIGHT(PHOTORES_sample *sample, PHOTORES_record *allTimeRecord, PHOTORES_sampleResult *res, clock_t *prevTimeStamp){
    int numberOfSamples = 0, numberOfDips = 0;
    clock_t endTime = clock() + 1000 * CLOCKS_PER_SEC/1000; // 1 second
    float reading;
    float threshold = allTimeRecord->averageReading;
    float prevReading = allTimeRecord->averageReading - 0.30, tolerance = threshold/TOLERARANCEDIVISION;//tolerance = 0.2;
    long double timeInterval = 1.0;
    bool first = true;
    while (clock() < endTime){
        if (!first)
            sleepforXnanoseconds(1000000L);

        reading = (read_RIGHT()/A2D_MAX_READING)*A2D_VOLTAGE_REF_V;
        // Set sample values
        sample[numberOfSamples].A2DReading = reading;
        sample[numberOfSamples].time = clock() - allTimeRecord->startTime;
        sample[numberOfSamples].timeInterval = timeInterval;

        if (!(first)){
            timeInterval = ((long double)(sample[numberOfSamples].time - *prevTimeStamp) / 1000000.0F) * 1000;
        }
        else
            first = false;

        // Find new max/min sample value
        if (reading > allTimeRecord->maxSample){
            allTimeRecord->maxSample = reading;
        }
        if (reading < allTimeRecord->minSample){
            allTimeRecord->minSample = reading;
        }

        // Find new max/min interval
        if (timeInterval > allTimeRecord->maxInterval){
            allTimeRecord->maxInterval = timeInterval;
        }
        if (timeInterval < allTimeRecord->minInterval){
            allTimeRecord->minInterval = timeInterval;
        }

        // Determine if dip occurred
        if (prevReading > threshold - tolerance && reading < threshold - tolerance){
            numberOfDips++;
        }

        *prevTimeStamp = sample[numberOfSamples].time;
        prevReading = reading;
        numberOfSamples++;
    }
    res->numberOfDips = numberOfDips;
    res->numberOfSamples = numberOfSamples;
    
}

void PHOTORES_LEFT(PHOTORES_sample *sample, PHOTORES_record *allTimeRecord, PHOTORES_sampleResult *res, clock_t *prevTimeStamp){
    int numberOfSamples = 0, numberOfDips = 0;
    clock_t endTime = clock() + 1000 * CLOCKS_PER_SEC/1000; // 1 second
    float reading;
    float threshold = allTimeRecord->averageReading;
    float prevReading = allTimeRecord->averageReading - 0.30, tolerance = threshold/TOLERARANCEDIVISION;//tolerance = 0.2;
    long double timeInterval = 1.0;
    bool first = true;
    while (clock() < endTime){
        if (!first)
            sleepforXnanoseconds(1000000L);

        reading = (read_LEFT()/A2D_MAX_READING)*A2D_VOLTAGE_REF_V;
        // Set sample values
        sample[numberOfSamples].A2DReading = reading;
        sample[numberOfSamples].time = clock() - allTimeRecord->startTime;
        sample[numberOfSamples].timeInterval = timeInterval;

        if (!(first)){
            timeInterval = ((long double)(sample[numberOfSamples].time - *prevTimeStamp) / 1000000.0F) * 1000;
        }
        else
            first = false;

        // Find new max/min sample value
        if (reading > allTimeRecord->maxSample){
            allTimeRecord->maxSample = reading;
        }
        if (reading < allTimeRecord->minSample){
            allTimeRecord->minSample = reading;
        }

        // Find new max/min interval
        if (timeInterval > allTimeRecord->maxInterval){
            allTimeRecord->maxInterval = timeInterval;
        }
        if (timeInterval < allTimeRecord->minInterval){
            allTimeRecord->minInterval = timeInterval;
        }

        // Determine if dip occurred
        if (prevReading > threshold - tolerance && reading < threshold - tolerance){
            numberOfDips++;
        }

        *prevTimeStamp = sample[numberOfSamples].time;
        prevReading = reading;
        numberOfSamples++;
    }
    res->numberOfDips = numberOfDips;
    res->numberOfSamples = numberOfSamples;
    
}

void PHOTORES_MIDDLE(PHOTORES_sample *sample, PHOTORES_record *allTimeRecord, PHOTORES_sampleResult *res, clock_t *prevTimeStamp){
    int numberOfSamples = 0, numberOfDips = 0;
    clock_t endTime = clock() + 1000 * CLOCKS_PER_SEC/1000; // 1 second
    float reading;
    float threshold = allTimeRecord->averageReading;
    float prevReading = allTimeRecord->averageReading - 0.30, tolerance = threshold/TOLERARANCEDIVISION;//tolerance = 0.2;
    long double timeInterval = 1.0;
    bool first = true;
    while (clock() < endTime){
        if (!first)
            sleepforXnanoseconds(1000000L);

        reading = (read_MIDDLE()/A2D_MAX_READING)*A2D_VOLTAGE_REF_V;
        // Set sample values
        sample[numberOfSamples].A2DReading = reading;
        sample[numberOfSamples].time = clock() - allTimeRecord->startTime;
        sample[numberOfSamples].timeInterval = timeInterval;

        if (!(first)){
            timeInterval = ((long double)(sample[numberOfSamples].time - *prevTimeStamp) / 1000000.0F) * 1000;
        }
        else
            first = false;

        // Find new max/min sample value
        if (reading > allTimeRecord->maxSample){
            allTimeRecord->maxSample = reading;
        }
        if (reading < allTimeRecord->minSample){
            allTimeRecord->minSample = reading;
        }

        // Find new max/min interval
        if (timeInterval > allTimeRecord->maxInterval){
            allTimeRecord->maxInterval = timeInterval;
        }
        if (timeInterval < allTimeRecord->minInterval){
            allTimeRecord->minInterval = timeInterval;
        }

        // Determine if dip occurred
        if (prevReading > threshold - tolerance && reading < threshold - tolerance){
            numberOfDips++;
        }

        *prevTimeStamp = sample[numberOfSamples].time;
        prevReading = reading;
        numberOfSamples++;
    }
    res->numberOfDips = numberOfDips;
    res->numberOfSamples = numberOfSamples;
    
}

float PHOTORES_exponentialAverage(float *prevAverageReading, PHOTORES_sample *sample, int size){
    float weight = 0.999;
    for (int i = 0; i < size; i++){
        *prevAverageReading = weight*(*prevAverageReading) + (1.0 - weight)*(sample[i].A2DReading);
    }
    return *prevAverageReading;
}

float PHOTORES_averageReading(PHOTORES_sample *data, int size){
    float sum = 0;
    for (int i = 0; i < size; i++){
        sum += data[i].A2DReading;
    }
    return sum/(float)size;
}