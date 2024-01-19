#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <GL/glut.h>

#include "../include/ui.h"
#include "../include/draws.h"
#include "../include/handler.h"
#include "../include/defines.h"
#include "../include/quarters.h"
#include "../include/gstructs.h"

/**
 * @brief initialize bikes and clients tuple list
 * 
 */
void init_list(void)
{
    _global_bc_list = create_list();
}