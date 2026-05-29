#include "sphere.h"
#include <stdlib.h>
#include <float.h>

static bool sphere_hit(const void *self, ray r,
                       double t_min, double t_max,
                       hit_record *rec)
{
    const sphere *s = self;
    vec3 oc = v3_sub(r.origin, s->center);
    double a = v3_dot(r.direction, r.direction);
    double b = v3_dot(oc, r.direction);
    double c = v3_dot(oc, oc) - s->radius*s->radius;
    double discriminant = b*b - a*c;
    if (discriminant > 0){
        double root = sqrt(discriminant);
        double temp = (-b - root) / a;
        if (temp < t_max && temp > t_min){
            rec->t = temp;
            rec->p = ray_at(r,temp);
            rec->normal = v3_div(
                    v3_sub(rec->p, s->center),
                    s->radius);
            rec->mat = s->mat;
            return true;
        }
        temp = (-b + root) / a;
        if (temp < t_max && temp > t_min){
            rec->t = temp;
            rec->p = ray_at(r,temp);
            rec->normal = v3_div(
                    v3_sub(rec->p, s->center),
                    s->radius);
            rec->mat = s->mat;
            return true;
        }
    }
    return false;
}

static const hitable_vtbl sphere_vtbl = { sphere_hit };

const hitable *sphere_new(vec3 c, double r, const material *m){
    sphere *s = malloc(sizeof *s);
    s->base.vtbl = &sphere_vtbl;
    s->center=c; s->radius=r; s->mat=m;
    return (hitable*)s;
}
