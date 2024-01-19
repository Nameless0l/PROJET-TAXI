#include "../include/gData_list.h"

HeadGData *create_gData_head(){
    HeadGData *headGData = (HeadGData*)malloc(sizeof(HeadGData));

    if(!headGData) return NULL;

    headGData->first = NULL;
    headGData->n = 0;

    return headGData;
}

void appendGData(HeadGData *headGData, pid_t bike_pid, int bike_start, pid_t client_pid, int client_start, int client_dest){
    GData *new_gData = (GData*)malloc(sizeof(GData));

    if(!new_gData){
        perror("appendGData");
        exit(EXIT_FAILURE);
    }

    new_gData->bike_pid = bike_pid;
    new_gData->bike_start = bike_start;

    new_gData->client_pid = client_pid;
    new_gData->client_start = client_start;
    new_gData->client_dest = client_dest;
    
    new_gData->next = NULL;

    if(!headGData->first)
        headGData->first = new_gData;
    else{
        GData *curGData = headGData->first;

        while(curGData->next)
            curGData = curGData->next;

        curGData->next = new_gData;
    }

    headGData->n++;
}

void clear_gDatas(HeadGData *headGData){
    GData *cur_data = headGData->first;

    while(cur_data){
        GData *to_free = cur_data;
        cur_data = cur_data->next;
        free(to_free);
    }

    headGData->n = 0;
    headGData->first = NULL;
}
