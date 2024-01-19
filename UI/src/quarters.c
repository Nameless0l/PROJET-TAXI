#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "../include/ui.h"
#include "../include/defines.h"
#include "../include/gstructs.h"
#include "../include/quarters.h"



const char *quaters_str[111] = 
{
    "Centre", "Elig Essono", "Etoa Meki I", "Nlongkak", "Elig_Edzoa", "Bastos", "Manguier", 
    "Tongolo", "MballaI", "MballaII", "Nkolondom", "Etoudi", "Messassi", "Okolo", "Olembe", "Nyom",
    "Etoa_MekiII", "MballaIII", "Emana", "Nkoleton", "CiteVerte", "Madagascar", "Mokolo", "GrandMessa",
    "Ekoudou", "Tsinga", "Nkom_Kana", "Oliga", "MessaCarrière", "EcoledePolice", "Febe", "Ntoungou","Obili",
    "Ngoa_EkeleI", "NlongMvolye", "AhalaI", "Efoulan", "Obobogo", "Nsam", "MelenII", "Etoa",
    "NkolmessengI", "AfanoyaI", "AfanoyaII", "AfanoyaIII", "AfanoyaIV", "Nkolfon", "MekoumbouII", "Ntouessong",
    "MekoumbouI", "AhalaII", "NsimeyongI", "NsimeyongII", "NsimeyongIII", "Olezoa", "Dakar", "Ngoa_EkeleII",
    "Mvan_Nord," "Ndamvout", "Messame_Ndongo", "Odza", "Ekoumdoum", "Awae", "Nkomo", "Ekounou", "Biteng",
    "KondenguiI", "Mimboman_I", "Etam_Bafia", "Mvog_Mbi",  "Nkol_NdongoII", "Mebandan", "Mvan_Sud","Ekie","Emombo", 
    "KondenguiII", "KondenguiIII", "Nkol_NdongoI", "MimbomanIII", "Ntui_Essong", "Nkolo","Abom","Mvog_Ada", "Essos"
    "Nkol_Messing", "Nkol_Ebogo", "QuartierFouda", "NgoussoI", "Eleveur", "MfandenaI", "MfandenaII", "NgoussoIII","Ngousso_Ntem", 
    "Ngoulmekong", "MelenVIIIBetC", "Etoug_EbeII", "Mvog_betsi", "Biyem_Assi", "MendongII", "MelenVIII","Simbock", "Etoug_EbeI", 
    "Melen", "Elig_Effa", "Nkolbikok", "SimbockEcoledeguerre", "Etetak", "Oyom_Abang", "Nkolbisson","Minkoameyos","Nkolso"
};



/** 
 * @brief init global quarters list 
 * 
 */
void init_quarters(void)
{
    _global_list_quarters = (G_quarter*)malloc(NB_QUARTERS * sizeof(G_quarter));
    for (int i = 0; i < NB_QUARTERS; ++i)
    {
        _global_list_quarters[i].id = i;
        _global_list_quarters[i].center = (Point*)malloc(sizeof(Point));
        _global_list_quarters[i].center->x = rand()%WIDTH;
        _global_list_quarters[i].center->y = rand()%HEIGHT;
    }
}


/**
 * @brief Function to find the coordinates of a quarter based on its ID. 
 * 
 * @param id
 * @return Point* 
 */
Point* get_quarter_pos(int id)
{
    Point* p = (Point*)malloc(sizeof(Point));
    for (int i = 0; i < NB_QUARTERS; ++i)
    {
        if (_global_list_quarters[i].id == id)
        {
            p->x = _global_list_quarters[i].center->x;
            p->y = _global_list_quarters[i].center->y;

            return p;
        }
    }

    p->x = _global_list_quarters[0].center->x;
    p->y = _global_list_quarters[0].center->y;
    return p;
}


/**
 * @brief Get the quarter str representation from an id
 * 
 * @param id 
 * @return const char* 
 */
const char* get_quarter_str(int id)
{
        if (id >= 0 && id < (sizeof(quaters_str) / sizeof(quaters_str[0])))
            return quaters_str[id];
    return NULL;
}


/**
 * @brief compute euclidian distance between 02 2D points
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float euclidian_dist(Point *a, Point *b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    return dx * dx + dy * dy;
}


/**
 * @brief draw quarters borders, algorithm based on voronoi diagram
 * 
 */
static Point* to_display = NULL;
static int borders_points_nb = 0;
static bool borders_computed = 0;
void draw_quarters_borders(void)
{   
    // if never computed borders
    if (!borders_computed)
    {
        // create map
        int** map = (int**)malloc(WIDTH * sizeof(int*));
        for (int i = 0; i < WIDTH; ++i)
            map[i] = (int*)malloc(HEIGHT * sizeof(int));

        // voronoi diagram
        for (int i = 0; i < WIDTH; ++i)
        {
            for (int j = 0; j < HEIGHT; ++j)
            {
                Point p = {i, j};
                int closest_id = 0;
                float min_dist = euclidian_dist(_global_list_quarters[0].center, &p);

                for (int k = 1; k < NB_QUARTERS; ++k)
                {
                    float dist = euclidian_dist(_global_list_quarters[k].center, &p);
                    if (dist < min_dist)
                    {
                        min_dist = dist;
                        closest_id = k;
                    }
                }
                map[i][j] = closest_id;
            }
        }

        // computes the number of points making borders
        for (int i = 0; i < WIDTH; ++i)
            for (int j = 1; j < HEIGHT; ++j)
                if (map[i][j] != map[i][j-1])
                    ++borders_points_nb;

        // saving borders points
        to_display = (Point*)malloc(borders_points_nb * sizeof(Point));
        int inc = 0;
        for (int i = 0; i < WIDTH; ++i)
        {
            for (int j = 1; j < HEIGHT; ++j)
            {
                if (map[i][j] != map[i][j-1])
                {
                    to_display[inc].x = i;
                    to_display[inc].y = j;
                    ++inc;
                }
            }
        }

        //freeing map
        for (int i = 0; i < WIDTH; ++i)
            free(map[i]);
        free(map);       

        // disable future recomputations
        borders_computed = true;
    }

    // start drawing
    glColor3ub(20, 20, 20);
    for (int i = 0; i < borders_points_nb; ++i)
    {
        glBegin(GL_POINTS);
        glVertex2d(to_display[i].x, to_display[i].y);
        glEnd();
    }
}