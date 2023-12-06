#ifndef __BIKE_LIST_H__
#define __BIKE_LIST_H__

#include "shared.h"
#include <stdio.h>
#include <stdlib.h>

HeadGData *create_gData_head();
void appendGData(HeadGData *headGData, pid_t bike_pid, int bike_start, pid_t client_pid, int client_start, int client_dest);
void clear_gDatas(HeadGData *headGData);
void displayGData(HeadGData *headGData);

#endif //__BIKE_LIST_H__


