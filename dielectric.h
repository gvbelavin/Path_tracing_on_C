#ifndef DIELECTRIC_H
#define DIELECTRIC_H
#include "material.h"

typedef struct {
    material base;
    double ref_idx;
} dielectric;

const material *dielectric_new(double ri);
#endif