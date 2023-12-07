#ifndef __UI_H_INCLUDED__
#define __UI_H_INCLUDED__

#include "./list.h"
#include "./gstructs.h"

// global vars
extern list_t *_global_bc_list;
extern G_quarter* _global_list_quarters;

void init_list(void);

#endif //__UI_H_INCLUDED__