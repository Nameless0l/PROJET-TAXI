#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/deque.h"


/**
 * @brief create a new block in a deque data structure.
 * 
 * @param pid(pid_t) the pid that will be stored in the block
 * @return block* a pointer to the newly block created
 */
block *create_block(pid_t pid)
{
    block *new_block = (block *)malloc(sizeof(block));
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
 * @brief  frees the memory allocated for a block in a deque data structure
 * 
 * @param b a pointer to the block that needs to be freed
 */
void free_block(block *b)
{
    free(b);
}


/**
 * @brief Create a deque object
 * 
 * @return deque* deque created
 */
deque *create_deque()
{
    deque *new_deque = (deque *)malloc(sizeof(deque));
    if (new_deque == NULL) 
    {
        perror("Error, canot create deque\n");
        exit(EXIT_FAILURE);
    }

    new_deque->start = NULL;
    new_deque->end = NULL;
    return new_deque;
}


/**
 * @brief destroy deque object
 * 
 * @param deque(deque) input deque to destroy
 */
void destroy_deque(deque *deque)
{
    block *current = deque->start;
    while (current != NULL)
    {
        block *temp = current;
        current = current->next;
        free(temp);
    }

    deque->start = NULL;
    deque->end = NULL;
    free(deque);
}


/**
 * @brief Pushes a new data value onto the front of the deque by allocating a new block
 * 
 * @param deque(deque) input deque
 * @param pid(pid_t) the pid to insert
 */
void push_front(deque *deque, pid_t pid)
{
    block *new_block = create_block(pid);
    if (deque->start == NULL) 
    {
        deque->start = new_block;
        deque->end = new_block;
    } 
    else 
    {
        new_block->next = deque->start;
        deque->start = new_block;
    }
}


/**
 * @brief pushes a new data value onto the back of the deque by allocating a new block
 * 
 * @param deque(deque) input deque 
 * @param pid(pid_t)
 */
void push_back(deque *deque, pid_t pid)
{
    block *new_block = create_block(pid);
    fprintf(stderr, "inside push with %d--\n", pid);
    if (deque->end == NULL) 
    {
        // La deque est vide
        deque->start = new_block;
        deque->end = new_block;
    } 
    else 
    {
        deque->end->next = new_block;
        deque->end = new_block;
    }
}


/**
 * @brief removes and returns the data at the front of the deque
 * 
 * @param deque(deque) input deque
 * @return pid_t poped item
 */
pid_t pop_front(deque *deque)
{
    if (deque->start == NULL) 
    {
        fprintf(stderr, "Error, deque is empty\n");
        exit(EXIT_FAILURE);
    }

    block *front_block = deque->start;
    pid_t pid = front_block->pid;

    if (deque->start == deque->end) 
    {
        deque->start = NULL;
        deque->end = NULL;
    } 
    else 
        deque->start = front_block->next;

    free_block(front_block);

    return pid;
}


/**
 * @brief deletes the block containing the given data value from the deque
 * 
 * @param deque(deque) input deque
 * @param pid(pid_t) pid to search and delete
 */
void delete_block(deque *deque, pid_t pid)
{
    block *current = deque->start;
    block *prev = NULL;

    while (current != NULL && current->pid != pid) 
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL) 
    {
        printf("Element %d not found in the deque\n", pid);
        return;
    }

    if (prev == NULL) 
        deque->start = current->next;
    else 
        prev->next = current->next;

    if (current != NULL)
        free(current);
}

/**
 * @brief print all values(pids) inside the deque
 * 
 * @param deq deque
 */
void print_deque(deque *deq)
{
    block *cur = deq->start;
    printf("[");
    while (cur != NULL)
    {
        printf("%d, ", cur->pid);
        cur = cur->next;
    }
    printf("]\n"); fflush(stdout);
}


int count_deque_values(deque *deq)
{
    int res = 0;
    block *cur = deq->start;
    while (cur != NULL)
    {
        ++res;
        cur = cur->next;
    }

    return res;
}
