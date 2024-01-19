#ifndef __SHARED_H_INCLUDED__
#define __SHARED_H_INCLUDED__

#include <time.h>

#define RADIUS 5

typedef struct Bike
{
   pid_t pid;
   int itinerary[5];
   int start;
}Bike;

typedef struct Client
{
    pid_t pid;
    int start;
    int dest;
    unsigned int price;
    time_t wait_time;
}Client;

typedef struct gData GData;
typedef struct headGData HeadGData;

struct headGData{
    int n;
    GData *first;
};

struct gData{
    pid_t bike_pid, client_pid;
    int bike_start;
    int client_start, client_dest;

    GData *next;
};

#endif // __SHARED_H_INCLUDED__