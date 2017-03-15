#ifndef __RAYTRACING_H
#define __RAYTRACING_H

#include "objects.h"
#include <stdint.h>

typedef struct __RAY_DETAIL {
    uint8_t *pixels;
    double *background_color;
    rectangular_node rectangulars;
    sphere_node spheres;
    light_node lights;
    const viewpoint *view;
    int width;
    int height;
    int tid;
    int tnum;
} raydetail;

raydetail *set_raydetail(uint8_t *pixels, color background_color,
                         rectangular_node rectangulars, sphere_node spheres,
                         light_node lights, const viewpoint *view,
                         int width, int height, int tid, int tnum);

void raytracing(void *raydetail);

#endif
