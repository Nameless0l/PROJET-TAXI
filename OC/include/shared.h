#ifndef __SHARED_H_INCLUDED__
#define __SHARED_H_INCLUDED__

#define RADIUS 5
#include <time.h>

typedef struct Bike
{
   pid_t pid;
   int *itinerary;
}Bike;

typedef struct Client
{
    pid_t pid;
    int start;
    int dest;
    unsigned int price;
    time_t wait_time;
}Client;

#endif // __SHARED_H_INCLUDED__