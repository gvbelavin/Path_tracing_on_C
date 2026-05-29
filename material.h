#ifndef MATERIAL_H
#define MATERIAL_H
#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "hit.h"

typedef struct material_vtbl {
    bool (*scatter)(const void *self,
                    ray r_in,
                    const hit_record *rec,
                    vec3 *atten,
                    ray  *scattered);
} material_vtbl;

typedef struct material {
    const material_vtbl *vtbl;
} material;


#endif
