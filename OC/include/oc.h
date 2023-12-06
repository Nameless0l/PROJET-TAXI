#ifndef __OC_H_INCLUDED__
#define __OC_H_INCLUDED__

#include <sys/types.h>
#include "./list.h"
#include "./defines.h"

extern List *bikes_list;
extern List *clients_list;

typedef int bool;

#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "../include/oc.h"
#include "../include/list.h"
#include "../include/shared.h"
#include "../include/defines.h"
#include "../include/handlers.h"

#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "../include/oc.h"
#include "../include/list.h"
#include "../include/shared.h"
#include "../include/defines.h"
#include "../include/handlers.h"
#include "../include/gData_list.h"

extern void *ui_shm;
extern HeadGData *corresponding_gDatas;

void schedule(pid_t ui_pid);
void delete_assigned(List *list, List *assigned);
void my_sleep();
void init_lists();
void init_oc();
void end_oc(pid_t ui_pid);
bool check_shm_exist(pid_t pid);
void create_ui_memory();
void set_blocking_signals(sigset_t *new_sig_set);
bool bike_founded(Bike *bike, Client *client);
void *get_shm(pid_t pid);
void write_structures_in_ui_shm(HeadGData *corresponding_gDatas, pid_t ui_pid);
void oc_log(List *bikes_list, List *clients_list);

typedef enum state
{
    _taken=0,
    _free=1
}state;

#endif // __OC_H_INCLUDED__