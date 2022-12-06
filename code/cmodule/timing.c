#include "includes/timing.h"

// Inspiration from 
// https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

void sleepforXnanoseconds(long X){
   struct timespec tim, tim2;
   tim.tv_sec = 0;
   tim.tv_nsec = X;
   nanosleep(&tim , &tim2);
}