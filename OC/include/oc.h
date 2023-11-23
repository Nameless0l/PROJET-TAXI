#ifndef __OC_H_INCLUDED__
#define __OC_H_INCLUDED__

#include <sys/types.h>
#include "deque.h"

extern deque *bikes_deque;
extern deque *clients_deque;

void end_oc();
void init_oc();

void* get_shm(pid_t pid);

void init_queues();
void init_sig_handlers();

void schedule();
#endif // __OC_H_INCLUDED__