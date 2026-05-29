#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "material.h"

typedef struct {
    material base;
    vec3 albedo;
} lambertian;

const material *lambertian_new(vec3 albedo);
#endif