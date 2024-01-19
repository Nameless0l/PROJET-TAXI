#ifndef __DEQUE_H_INCLUDED__
#define __DEQUE_H_INCLUDED__

#include "./gstructs.h"
#include "./defines.h"
#include <sys/types.h>

typedef int bool;

// node of the deque
typedef struct block_t 
{
    pid_t bike_pid;
    pid_t client_pid;
    bool course_ended;

    G_bike* gbike;
    G_client* gclient;

    struct block_t *next;
}block_t;

// deque 
typedef struct list_t
{
    struct block_t* start;
}list_t;

// block creation
block_t *create_block(pid_t bike_pid, pid_t client_pid, G_bike *b, G_client *c);

// create list
list_t *create_list();

// destroy list
void destroy_list(list_t *list);

// push at top of the deque
void push_front(list_t *list, pid_t bike_pid, pid_t client_pid, G_bike *b, G_client *c);

// delete element at the top of the deque
void pop_front(list_t *list);

// searh and delete block in the deque
void delete_block(list_t *list, pid_t bike_pid, pid_t client_pid);

#endif // __DEQUE_H_INCLUDED__