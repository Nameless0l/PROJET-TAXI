#ifndef __HANDLERS_H_INCLUDED__
#define __HANDLERS_H_INCLUDED__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


#include "defines.h"


void handle_client_create(int signum, siginfo_t *info, void *context);
void handle_bike_create(int signum, siginfo_t *info, void *context);
void handle_client_gone(int signum, siginfo_t *info, void *context);

#endif // __HANDLERS_H_INCLUDED__