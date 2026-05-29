#ifndef RAY_H
#define RAY_H
#include "vec3.h"

typedef struct {
    vec3 origin;
    vec3 direction;
} ray;

static inline vec3 ray_at(ray r, double t){
    return v3_add(r.origin, v3_scale(r.direction, t));
}

#endif
