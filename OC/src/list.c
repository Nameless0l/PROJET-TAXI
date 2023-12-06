#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/list.h"

/**
 * @brief Create a list object
 * @return list* list created
 */
List *create_list()
{
    List *new_list = (List*)malloc(sizeof(List));
    if (!new_list) 
    {
        perror("Error, canot create list\n");
        exit(EXIT_FAILURE);
    }

    new_list->start = NULL;

    return new_list;
}

/**
 * @brief destroy list object
 * @param list(list) input list to destroy
 */
void destroy_list(List *list)
{
    Block *cur_block = list->start;

    while(cur_block){
        Block *block_to_delete = cur_block;
        cur_block = cur_block->next;
        free(block_to_delete);
    }

    free(list);
}

/**
 * @brief create a new block in a list data structure.
 * @param pid(pid_t) the pid that will be stored in the block
 * @return block* a pointer to the newly block created
 */
Block *create_block(pid_t pid)
{
    Block *new_block = (Block*)malloc(sizeof(Block));
    if (new_block == NULL) 
    {
        perror("Block allocation error");
        exit(EXIT_FAILURE);
    }

    new_block->pid = pid;
    new_block->next = NULL;
    
    return new_block;
}

/**
 * @brief  frees the memory allocated for a block in a list data structure
 * @param b a pointer to the block that needs to be freed
 */
void free_block(Block *b)
{
    free(b);
}

/**
 * @brief Pushes a new data value onto the front of the list by allocating a new block
 * @param list(list) input list
 * @param pid(pid_t) the pid to insert
 */
void push_front(List *list, pid_t pid)
{
    Block *new_block = create_block(pid);
    
    if (list->start)        
        new_block->next = list->start;

    list->start = new_block;
}

/**
 * @brief pushes a new data value onto the back of the list by allocating a new block
 * 
 * @param list(list) input list 
 * @param pid(pid_t)
 */
void push_back(List *list, pid_t pid)
{
    Block *new_block = create_block(pid);

    if (!list->start)
        list->start = new_block;
    else
    {
        Block *cur_block = list->start;

        while(cur_block->next)
            cur_block = cur_block->next;

        cur_block->next = new_block;
    }
}

/**
 * @brief removes and returns the data at the front of the list
 * @param list(list) input list
 * @return pid_t poped item
 */
pid_t pop_front(List *list)
{
    if (list->start == NULL)
    {
        fprintf(stderr, "Error, list is empty\n");
        exit(EXIT_FAILURE);
    }

    Block *front_block = list->start;
    pid_t pid = front_block->pid;

    list->start == list->start->next;

    free_block(front_block);

    return pid;
}


/**
 * @brief deletes the block containing the given data value from the list
 * @param list(list) input list
 * @param pid(pid_t) pid to search and delete
 */
void delete_block(List *list, pid_t pid)
{
    Block *cur_block = list->start;
    Block *prev_block = NULL;

    while(cur_block && cur_block->pid != pid)
    {
        prev_block = cur_block;
        cur_block = cur_block->next;
    }

    if(!cur_block) return;

    if(list->start == cur_block)
        list->start = list->start->next;
    
    if(prev_block)
        prev_block->next = cur_block->next;

    free(cur_block);
}

/**
 * @brief print all values(pids) inside the list
 * 
 * @param deq list
 */
void print_list(char *s, List *list)
{
    printf("\t> %s (%d) : [", s, count_list_values(list));
    
    Block *cur = list->start;
    if(cur){
        printf("%d", cur->pid);
     
        cur = cur->next;
        while (cur)
        {
            printf(", %d", cur->pid);
            cur = cur->next;
        }
    }

    printf("]\n");
    fflush(stdout);
}

void print_lists(List *bikes_list, List *clients_list){
    print_list("Bikes list", bikes_list);
    print_list("Clients list", clients_list);
}

int count_list_values(List *list)
{
    int n = 0;
    for(Block *cur_block = list->start; cur_block; cur_block = cur_block->next) ++n;

    return n;
}
