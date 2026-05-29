#ifndef HIT_H
#define HIT_H
#include <stdbool.h>
#include "ray.h"

struct material;

typedef struct {
    double t;
    vec3   p;
    vec3   normal;
    const struct material *mat;
} hit_record;

typedef struct hitable_vtbl {
    bool (*hit)(const void *self,
                ray r, double t_min, double t_max,
                hit_record *rec);
} hitable_vtbl;

typedef struct {
    const hitable_vtbl *vtbl;
} hitable;

#endif /* HIT_H */