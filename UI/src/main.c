#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>

#include "../include/ui.h"
#include "../include/list.h"
#include "../include/draws.h"
#include "../include/handler.h"
#include "../include/defines.h"
#include "../include/quarters.h"


list_t* _global_bc_list;
G_quarter* _global_list_quarters;

int main(int argc, char* argv[])
{
    init_list();
    init_handlers();
    init_quarters();
    srand(time(NULL));

    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    printf("UI PID : %d \n", getpid());
    fflush(stdout);

    glutInitWindowSize(WIDTH * DPI_SCALE, HEIGHT * DPI_SCALE);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH * DPI_SCALE) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT * DPI_SCALE) / 2);
    glutCreateWindow("Bikes Project : User's interface");

    // Mapping definition
    glTranslatef(-1, -1, 0);
    glScalef(2.0 / WIDTH, 2.0 / HEIGHT, 1.0);

    glutDisplayFunc(ui_display); 
    glutTimerFunc(10, update_pos, 0);

    glutMainLoop();
    // */
}