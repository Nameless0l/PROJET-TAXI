#ifndef __DEQUE_H_INCLUDED__
#define __DEQUE_H_INCLUDED__

#include <sys/types.h>

typedef struct block Block;
typedef struct list List;

// node of the list
struct block
{
    pid_t pid;
    Block *next;
};

// list 
struct list 
{
    Block *start;
};

List *create_list();
void destroy_list(List *list);
Block *create_block(pid_t pid);
void free_block(Block *b);
void push_front(List *list, pid_t pid);
void push_back(List *list, pid_t pid);
pid_t pop_front(List *list);
void delete_block(List *list, pid_t pid);
void print_list(char *s, List *list);
void print_lists(List *bikes_list, List *clients_list);
int count_list_values(List *list);

#endif // __DEQUE_H_INCLUDED__