#ifndef __DEQUE_H_INCLUDED__
#define __DEQUE_H_INCLUDED__

#include <sys/types.h>


// node of the deque
typedef struct block 
{
    pid_t pid;
    struct block *next;
}block;

// deque 
typedef struct deque 
{
    struct block *start;
    struct block *end;
}deque;

// block creation
block *create_block(pid_t pid);

// count deque blocks
int count_deque_values(deque *deq);

// print deque blocks
void print_deque(deque *deq);

// free block
void free_block(block *block);

// create deque
deque *create_deque();

// destroy deque
void destroy_deque(deque *deque);

// push at top of the deque
void push_front(deque *deque, pid_t pid);

// push at end of the deque
void push_back(deque *deque, pid_t pid);

// delete element at the top of the deque
pid_t pop_front(deque *deque);

// delete element at the end of the deque
pid_t pop_back(deque *deque);

// searh and delete block in the deque
void delete_block(deque *deque, pid_t pid);

#endif // __DEQUE_H_INCLUDED__