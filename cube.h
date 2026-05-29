#ifndef CUBE_H
#define CUBE_H

#include "hit.h"
#include "material.h"

typedef struct {
    hitable base;
    vec3 min;    // Минимальная точка (нижний левый задний угол)
    vec3 max;    // Максимальная точка (верхний правый передний угол)
    const material *mat;
} cube;

const hitable *cube_new(vec3 min, vec3 max, const material *m);

#endif
