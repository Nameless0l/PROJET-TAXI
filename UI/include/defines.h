#ifndef __DEFINES_H_INCLUDED__
#define __DEFINES_H_INCLUDED__

#include <GL/glut.h>

#define WIDTH 1280
#define HEIGHT 768
#define DPI_SCALE glutGet(GLUT_SCREEN_WIDTH) / 1920

#define _RADIUS 20
#define _SIDE _RADIUS * 2 + 5

#define CLIENT_R 0.45
#define CLIENT_G 0.76
#define CLIENT_B 0.98

#define BIKE_R 0.39
#define BIKE_G 0.84
#define BIKE_B 0.34

#define SPEED 1

#define true 1
#define false 0

#define NB_QUARTERS 110
#define GEN_POINTS_FACTOR 1

#define OC_SHM_SIZE 2048
#define OC_HAS_SCHEDULED 0xE

#endif //__DEFINES_H_INCLUDED__