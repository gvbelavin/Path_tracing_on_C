#ifndef SPHERE_H
#define SPHERE_H
#include "hit.h"
#include "material.h"

typedef struct {
    hitable base;
    vec3 center;
    double radius;
    const material *mat;
} sphere;

const hitable *sphere_new(vec3 c, double r, const material *m);

#endif