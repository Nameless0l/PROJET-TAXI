#ifndef __HANDLER_H_INCLUDED__
#define __HANDLER_H_INCLUDED__

#include <signal.h>
#include <unistd.h>

void init_handlers();
void handle_oc_scheduled(int signum, siginfo_t *info, void *context);

#endif //__HANDLER_H_INCLUDED__