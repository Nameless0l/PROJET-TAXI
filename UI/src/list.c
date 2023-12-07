#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/list.h"
#include "../include/defines.h"


/**
 * @brief create a new block in a list data structure.
 * 
 * @param bike_pid(pid_t) bike pid
 * @param client_pid(pid_t) client_pid
 * @param b(G_bike*) graphic bike struct
 * @param c(G_client*) graphic client struct
 * @return block_t* new created block
 */
block_t *create_block(pid_t bike_pid, pid_t client_pid, G_bike *b, G_client *c)
{
    block_t *new_block = (block_t *)malloc(sizeof(block_t));
    if (new_block == NULL) 
    {
        fprintf(stderr, "Block allocation error \n");
        exit(EXIT_FAILURE);
    }
    new_block->gbike = b;
    new_block->gclient = c;

    new_block->bike_pid = bike_pid;
    new_block->client_pid = client_pid;
    new_block->course_ended = false;
    new_block->next = NULL;

    return new_block;
}


/**
 * @brief Create a list object
 * 
 * @return list_t* created list
 */
list_t *create_list()
{
    list_t *new_list = (list_t*)malloc(sizeof(list_t));
    if (new_list == NULL) 
    {
        fprintf(stderr, "Error, cannot allocate for creating new list\n");
        exit(EXIT_FAILURE);
    }
    new_list->start = NULL;

    return new_list;
}


/**
 * @brief destroy list object
 * 
 * @param list(list_t) list to destroy
 */
void destroy_list(list_t *list)
{
    block_t *current = list->start;
    while (current != NULL)
    {
        block_t *temp = current;
        current = current->next;
        free(temp);
    }

    list->start = NULL;
    free(list);
}


/**
 * @brief create a new block from parmaeters and insert it at top of the list
 * 
 * @param list(list_t) input list
 * @param bike_pid(pid_t) bike_pid
 * @param client_pid(pid_t) client_pid
 * @param b(G_bike*) graphic bike structure
 * @param c(G_client*) graphic client structure
 */
void push_front(list_t *list, pid_t bike_pid, pid_t client_pid, G_bike *b, G_client *c)
{
    block_t *new_block = create_block(bike_pid, client_pid, b, c);
    if (list->start != NULL) 
        new_block->next = list->start;

    list->start = new_block;
}


/**
 * @brief removes the block at the top of the list
 * 
 * @param list(list_t*) input list
 */
void pop_front(list_t *list)
{
    if (list->start == NULL) 
    {
        fprintf(stderr, "Error, deque is empty\n");
        exit(EXIT_FAILURE);
    }

    block_t *front_block = list->start;
    list->start = list->start->next;
    free(front_block);
}


/**
 * @brief deletes the block containing the given params value from the list
 * 
 * @param list(list_t) input list
 * @param bike_pid(pid_t) bike pid
 * @param client_pid(pid_t) client_pid
 */
void delete_block(list_t *list, pid_t bike_pid, pid_t client_pid)
{
    block_t *current = list->start;
    block_t *prev = NULL;

    while (current != NULL && current->client_pid != client_pid && current->bike_pid != bike_pid) 
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL) 
    {
        printf("Element not found in the deque\n");
        return;
    }

    if (list->start == current)
        list->start = list->start->next;

    if (prev != NULL)
        prev->next = current->next;

    // feeeing gbike
    free(current->gclient->start);
    free(current->gclient->dest);
    free(current->gclient->center);

    // freeing gclient
    free(current->gbike->start);
    free(current->gbike->center);


    free(current);
}