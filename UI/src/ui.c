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
#include "../include/gstructs.h"


/**
 * @brief initialize bikes and clients tuple list
 * 
 */
void init_list(void)
{
    bikes_n_clients_list = create_list();
}



/** 
 * @brief Function to create many points for display and store them in a list_quarter. 
 * 
 */
void init_quaters_list() 
{
    list_quarters = (G_quarters**)malloc(sizeof(G_quarters*) * NB_QUATERS);

    for (int i = 0; i < NB_QUATERS; ++i)
    {
        G_quarters* q = (G_quarters*)malloc(sizeof(*q));
        q->id = i;
        q->loc = (Point*)malloc(sizeof(Point));
        q->loc->x = rand() % WIDTH;
        q->loc->y = rand() % HEIGHT;

        list_quarters[i] = q;
    }

    /*double radius1 = HEIGHT;
    double radius2 = WIDTH;
   
    int nb = 32;
    int a = 0;
    int total = 0;

    for (int i = 6; i > 1; i--) 
    {
      
        // Create a point.
        for (int j = 1; j < nb + 1; j++) 
        {
            G_Quarters Q;
            Q.id = a + j;
            if(i==6){Q.x=round((j/nb)*radius2);
            Q.y=round(0.33*radius1);}
            if(i==5){Q.x=round((j/nb)*radius2);
            Q.y=round(0.66*radius1);}
            if(i==4){Q.x=round(0.25*radius2);
            Q.y=round((j/nb)*radius1);}
            if(i==3){Q.x=round((j/nb)*radius1);
            Q.y=round(0.75*radius2);}
            else{Q.y=round((j/nb)*radius1);
            Q.x=round(0.5*radius2);}
            list_Quarters[Q.id] = Q;
            printf("quartier:%d ,%d ,%d\n",Q.id,Q.x,Q.y);
            total++;
        }
        
        a = a + nb;
        nb = nb - 5;
    }

    /*
    double radius1 = HEIGHT;
    double radius2 = WIDTH;
   
    int nb = 32;
    int a = 0;
    int total = 0;

    /*for (int i = 6; i > 1; i--) 
    {
        radius1 = (i - 1) * radius1 / 5.0;
        radius2 = (i - 1) * radius2 / 5.0;
       
        // Create a point.
        for (int j = 1; j < nb + 1; j++) 
        {
            G_quarters* q = (G_quaters*)malloc(sizeof(*q));
            q->id = a + j;
            q->x = round((radius2 * cos(j * PI / (2*nb))) * 10) / 10;
            q->y = round((radius1 * sin(j * PI / (2*nb))) * 10) / 10;
            list_quarters[Q.id] = Q;
            total++;
        }
        
        a += nb;
        nb -= 5;
        nb = nb - 5;
    } */
}


/**
 * @brief Function to find the coordinates of a quarter based on its ID. 
 * 
 * @param id(int) 
 * @return point 
 */
Point* get_quater_pos(int id)
{

    Point* p = (Point*)malloc(sizeof(Point));
    for (int i = 0; i < NB_QUATERS; ++i)
    {
        if (list_quarters[i]->id == id)
        {
            p->x = list_quarters[i]->loc->x;
            p->y = list_quarters[i]->loc->y;

            return p;
        }
    }

    p->x = 0.0;
    p->y = 0.0;
    return p;
}