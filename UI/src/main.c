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

list_t *bikes_n_clients_list;
G_quarters** list_quarters;

int main(int argc, char* argv[])
{
    init_list();
    init_handlers();
    srand(time(NULL));
    init_quaters_list();

    printf("UI PID : %d \n", getpid());
    fflush(stdout);

    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(WIDTH * DPI_SCALE, HEIGHT * DPI_SCALE);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH * DPI_SCALE) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT * DPI_SCALE) / 2);
    glutCreateWindow("Bikes Project : User's interface");

    // Mapping definition
    glTranslatef(-1, -1, 0);
    glScalef(2.0 / WIDTH, 2.0 / HEIGHT, 1.0);

    glutDisplayFunc(ui_display); 
    glutTimerFunc(10, update_pos, 0);

    glutMainLoop();
}