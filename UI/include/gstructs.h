#ifndef __G_STRUCTS_H_INCLUDED__
#define __G_STRUCTS_H_INCLUDED__

#include <unistd.h>

// 2D point structure
typedef struct Point
{
    float x;
    float y;
}Point;

//client's structure
typedef struct G_client
{
    float radius;
    Point* start;
    Point* dest;
    Point* center;
}G_client;

//bike's structure
typedef struct G_bike
{
    float side;
    Point* start;
    Point* center;
}G_bike;


typedef struct G_quarter 
{
    int id;
    Point *center;
} G_quarter;


typedef struct G_data
{
    pid_t bike_pid, client_pid;
    int bike_start;
    int client_start, client_dest;

    struct G_data* next;   
}G_data;

#endif //__G_STRUCTS_H_INCLUDED__