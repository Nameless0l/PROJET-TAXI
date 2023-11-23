#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>

#define STARTED_COURSE 0x3
#define SEGMENT_READY 0xa
#define TASK_TIME_MIN 5
#define TASK_TIME_MAX 10
#define SEG_SIZE 1024
#define BIKE_CREATED 0x5
#define NB_QUARTER 110
#define RADIUS 5
#define ENDED_COURSE 0x4
#define WAIT_TIME 1 

typedef struct{
   pid_t pid;
   int itinerary[5];
}Bike;

extern Bike *bike;
extern pid_t oc_pid;
extern int shm_id;	// id of area
extern void *shm_zone;	//attach area
extern key_t shm_key;	// clief of area
extern char *quartier[111];


#endif // __DEFINES_H__