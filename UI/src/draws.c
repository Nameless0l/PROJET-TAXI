#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

#include "../include/ui.h"
#include "../include/list.h"
#include "../include/draws.h"
#include "../include/defines.h"
#include "../include/quarters.h" 
#include "../include/gstructs.h"


/**
 * @brief main glut display callback function.
 * 
 */
void ui_display(void)
{
    fflush(stdout);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.104f, 0.104f, 0.104f, 1);    // clearing the screen with a gray color

    //setting graphics display options...
    glEnable(GL_BLEND);
    glEnable(GL_DOUBLEBUFFER);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glLineWidth(1.0f);
    glPointSize(3.0f);

    draw_grid();
    draw_quarters_borders();
    draw_quarters_mark();
    draw_quarters_names();
    draw_bc_list(_global_bc_list);
    
    glFlush();
    glutSwapBuffers();
}


/**
 * @brief draw a client on the screen
 * 
 * @param c the client graphic structure
 */
void draw_client(G_client *c)
{
    glColor3f(CLIENT_R, CLIENT_G, CLIENT_B);
    glLineWidth(5.0f);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 200.0f; ++i)
    {
        float angle = 2 * 3.141592653 * i / 200.0f;
        glVertex2f(cos(angle) * c->radius + c->center->x, sin(angle) * c->radius + c->center->y);
    }
    glEnd();

    glFlush();
}


/**
 * @brief draw a bike on the screen
 * 
 * @param b the bike graphic structure
 */
void draw_bike(G_bike *b)
{
    glColor3f(BIKE_R, BIKE_G, BIKE_B);
    glLineWidth(5.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(b->center->x - (b->side / 2), b->center->y - (b->side / 2));
    glVertex2f(b->center->x - (b->side / 2), b->center->y + (b->side / 2));
    glVertex2f(b->center->x + (b->side / 2), b->center->y + (b->side / 2));
    glVertex2f(b->center->x + (b->side / 2), b->center->y - (b->side / 2));
    glEnd();
}


/**
 * @brief draw all 
 * 
 */
void draw_quarters_mark()
{
    int gray = 20;
    float radius = 2.5f;
    glColor3ub(gray, gray, gray);
    glLineWidth(5.0f);

    for (int i = 0; i < NB_QUARTERS; ++i)
    {
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < 200.0f; ++j)
        {
            float angle = 2 * 3.141592653 * j / 200.0f;
            glVertex2f(cos(angle) * radius + _global_list_quarters[i].center->x, sin(angle) * radius + _global_list_quarters[i].center->y);
        }
        glEnd();
    }
    glFlush();
}


/**
 * @brief draw all quarters names 
 * 
 */
void draw_quarters_names(void)
{
    int gray = 100;
    glColor3ub(gray, gray, gray);
    glLineWidth(5.0f);


    for (int i = 0; i < NB_QUARTERS; ++i)
    {   
        glRasterPos3d(_global_list_quarters[i].center->x - 5, _global_list_quarters[i].center->y + 10, 0);
        const char* to_str = get_quarter_str(_global_list_quarters[i].id);
        if (to_str == NULL)
            continue;

        for (int j = 0; j < strlen(to_str); ++j)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, to_str[j]);
    }
    glFlush();
}


/**
 * 
 * @brief draw a grid on background
 * @return noreturn
 */
void draw_grid(void)
{
    glColor3ub(20, 20, 20);      //lines color

    // vertical lines
    for (float i = 0.0; i < WIDTH; i += 20)
    {
        glBegin(GL_LINES);
        glVertex2f(i, 0.0);
        glVertex2f(i, HEIGHT);
        glEnd();
    }

    //horizontal lines
    for (float i = 0.0; i < HEIGHT; i += 20)
    {
        glBegin(GL_LINES);
        glVertex2f(0.0, i);
        glVertex2f(WIDTH, i);
        glEnd();
    }

    glFlush();
}


/**
 * @brief draw gbikes and gvlients at the screen 
 * 
 */
static block_t* to_display;
void draw_bc_list(list_t *list)
{
    to_display = list->start;

    while (to_display != NULL) 
    {
        draw_bike(to_display->gbike);
        draw_client(to_display->gclient);
        to_display = to_display->next;
        glFlush();
    }

    glFlush();
}


static block_t* to_update;
void update_pos(int value)
{
    to_update = _global_bc_list->start;
    while(to_update != NULL)
    {
        if (to_update->course_ended) // if the course has ended, act as a deleter
        {
            block_t* tmp = to_update->next;
            delete_block(_global_bc_list, to_update->bike_pid, to_update->client_pid);
            to_update = tmp;
            
            continue;
        }

        if (to_update->gbike->center->x == to_update->gclient->center->x) // if the bike has already reached to the client position
        {
            // bike and client at client destination ie end of course
            if (to_update->gbike->center->x == to_update->gclient->dest->x && to_update->gclient->center->x == to_update->gclient->dest->x)
            {
                // mark the course as ended
                to_update->course_ended = true;

                continue;
            }
            
            // move client & bike to client destination
            float m = (to_update->gbike->center->y - to_update->gclient->dest->y) / (to_update->gbike->center->x - to_update->gclient->dest->x);
            int speed = (to_update->gbike->center->x > to_update->gclient->dest->x) ? -SPEED : SPEED;
            
            to_update->gbike->center->y += m * speed;
            to_update->gbike->center->x += speed;

            to_update->gclient->center->y += m * speed;
            to_update->gclient->center->x += speed;
        }
        else // bike not yet reached to client pos
        {
            float m = (to_update->gbike->center->y - to_update->gclient->center->y) / (to_update->gbike->center->x - to_update->gclient->center->x);
            int speed = (to_update->gbike->center->x > to_update->gclient->center->x) ? -SPEED : SPEED;

            to_update->gbike->center->y += m * speed;
            to_update->gbike->center->x += speed;
        }
        to_update = to_update->next;
    }
    
    glutPostRedisplay();
    glutTimerFunc(10, update_pos, value);
}