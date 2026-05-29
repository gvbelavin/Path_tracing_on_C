#ifndef METAL_H
#define METAL_H
#include "material.h"

typedef struct {
    material base;
    vec3  albedo;
    double fuzz;
} metal;

const material *metal_new(vec3 albedo, double fuzz);
#endif