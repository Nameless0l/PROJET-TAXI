#ifndef __UI_H_INCLUDED__
#define __UI_H_INCLUDED__

#include "./list.h"
#include "./gstructs.h"

extern list_t *bikes_n_clients_list;
extern G_quarters** list_quarters;

void init_list(void);
void init_quaters_list();
Point* get_quater_pos(int id);

#endif //__UI_H_INCLUDED__