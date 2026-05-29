#include <stdlib.h>
#include <math.h>
#include "dielectric.h"
#include "rng.h"

static vec3 reflect(vec3 v, vec3 n)
{
    return v3_sub(v, v3_scale(n, 2.0 * v3_dot(v, n)));
}

static bool refract(vec3 v, vec3 n, double ni_over_nt, vec3 *refracted)
{
    vec3 uv = v3_unit(v);
    double dt = v3_dot(uv, n);
    double d = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
    if (d > 0.0) {
        *refracted = v3_sub(
                v3_scale(v3_sub(uv, v3_scale(n, dt)), ni_over_nt),
                v3_scale(n, sqrt(d))
        );
        return true;
    }
    return false;
}

static double schlick(double cosine, double ref_idx)
{
    double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow(1.0 - cosine, 5.0);
}

static bool dielectric_scatter(const void *self,
                               ray in, const hit_record *rec,
                               vec3 *atten, ray *scattered)
{
    const dielectric *diel = self;
    vec3 outward_normal;
    vec3 reflected = reflect(in.direction, rec->normal);
    double ni_over_nt;
    *atten = v3(1.0, 1.0, 1.0);

    vec3 refracted;
    double cosine;
    if (v3_dot(in.direction, rec->normal) > 0) {
        outward_normal = v3_scale(rec->normal, -1.0);
        ni_over_nt = diel->ref_idx;
        cosine = diel->ref_idx *
                 v3_dot(in.direction, rec->normal) /
                 v3_len(in.direction);
    } else {
        outward_normal = rec->normal;
        ni_over_nt = 1.0 / diel->ref_idx;
        cosine = -v3_dot(in.direction, rec->normal) /
                 v3_len(in.direction);
    }

    double reflect_prob;
    if (refract(in.direction, outward_normal, ni_over_nt, &refracted)) {
        reflect_prob = schlick(cosine, diel->ref_idx);
    } else {
        reflect_prob = 1.0;
    }

    if (rng_double() < reflect_prob) {
        *scattered = (ray){ rec->p, reflected };
    } else {
        *scattered = (ray){ rec->p, refracted };
    }
    return true;
}

static const material_vtbl vtbl = { dielectric_scatter };

const material *dielectric_new(double ri)
{
    dielectric *d = malloc(sizeof *d);
    d->base.vtbl = &vtbl;
    d->ref_idx   = ri;
    return (material *)d;
}