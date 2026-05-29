#include <stdlib.h>
#include "lambertian.h"
#include "rng.h"
static bool lambertian_scatter(const void *self,
                               ray in, const hit_record *rec,
                               vec3 *atten, ray *scat)
{
    const lambertian *lam = self;
    vec3 target = v3_add(
            v3_add(rec->p, rec->normal),
            rng_in_unit_sphere());
    *scat   = (ray){ rec->p, v3_sub(target, rec->p) };
    *atten  = lam->albedo;
    return true;
}

static const material_vtbl lam_vtbl = { lambertian_scatter };

const material *lambertian_new(vec3 albedo){
    lambertian *m = malloc(sizeof *m);
    m->base.vtbl = &lam_vtbl;
    m->albedo = albedo;
    return (material*)m;
}
