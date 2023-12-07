#ifndef __QUARTERS_H_INCLUDED__
#define __QUARTERS_H_INCLUDED__

#include "./gstructs.h"

// methods
void draw_quarters(void);
void init_quarters(void);
Point* get_quarter_pos(int id);
void draw_quarters_borders(void);
const char* get_quarter_str(int id);

#endif //__QUARTERS_H_INCLUDED__