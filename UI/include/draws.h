#ifndef __DRAWS_H_INCLUDED__
#define __DRAWS_H_INCLUDED__

#include "./gstructs.h"

void draw_grid(void);
void draw_bike(G_bike *b);
void draw_client(G_client *c);
void draw_quarters_mark(void);
void draw_quarters_names(void);
void draw_bc_list(list_t *list);

void ui_display(void);
void update_pos(int value);
#endif //__DRAWS_H_INCLUDED__