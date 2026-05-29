#include <stdlib.h>
#include "metal.h"
#include "rng.h"

static vec3 reflect(vec3 v, vec3 n)
{
    return v3_sub(v, v3_scale(n, 2.0 * v3_dot(v, n)));
}

static bool metal_scatter(const void *self,
                          ray in, const hit_record *rec,
                          vec3 *atten, ray *scattered)
{
    const metal *m = self;
    vec3 reflected = reflect(v3_unit(in.direction), rec->normal);
    *scattered = (ray){
            rec->p,
            v3_add(reflected,
                   v3_scale(rng_in_unit_sphere(), m->fuzz))
    };
    *atten = m->albedo;
    return v3_dot(scattered->direction, rec->normal) > 0;
}

static const material_vtbl vtbl = { metal_scatter };

const material *metal_new(vec3 albedo, double fuzz)
{
    if (fuzz > 1.0) fuzz = 1.0;
    metal *m = malloc(sizeof *m);
    m->base.vtbl = &vtbl;
    m->albedo = albedo;
    m->fuzz   = fuzz;
    return (material *)m;
}
