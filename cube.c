#include "cube.h"
#include <stdlib.h>
#include <stdbool.h>

static bool cube_hit(const void *self, ray r, double t_min, double t_max, hit_record *rec) {
    const cube *c = self;

    // Определяем границы AABB
    double t_near = (c->min.x - r.origin.x) / r.direction.x;
    double t_far = (c->max.x - r.origin.x) / r.direction.x;

    if (t_near > t_far) {
        double temp = t_near;
        t_near = t_far;
        t_far = temp;
    }

    double y_near = (c->min.y - r.origin.y) / r.direction.y;
    double y_far = (c->max.y - r.origin.y) / r.direction.y;

    if (y_near > y_far) {
        double temp = y_near;
        y_near = y_far;
        y_far = temp;
    }

    if ((t_near > y_far) || (y_near > t_far)) {
        return false;
    }

    if (y_near > t_near) {
        t_near = y_near;
    }

    if (y_far < t_far) {
        t_far = y_far;
    }

    double z_near = (c->min.z - r.origin.z) / r.direction.z;
    double z_far = (c->max.z - r.origin.z) / r.direction.z;

    if (z_near > z_far) {
        double temp = z_near;
        z_near = z_far;
        z_far = temp;
    }

    if ((t_near > z_far) || (z_near > t_far)) {
        return false; // нет пересечения
    }

    if (z_near > t_near) {
        t_near = z_near;
    }

    if (z_far < t_far) {
        t_far = z_far;
    }

    if (t_near < t_max && t_far > t_min) {
        if (rec) {
            rec->t = t_near;
            rec->p = ray_at(r, rec->t);
            vec3 outward_normal;

            if (rec->p.x < c->min.x + 1e-6) outward_normal = v3(-1, 0, 0);
            else if (rec->p.x > c->max.x - 1e-6) outward_normal = v3(1, 0, 0);
            else if (rec->p.y < c->min.y + 1e-6) outward_normal = v3(0, -1, 0);
            else if (rec->p.y > c->max.y - 1e-6) outward_normal = v3(0, 1, 0);
            else if (rec->p.z < c->min.z + 1e-6) outward_normal = v3(0, 0, -1);
            else outward_normal = v3(0, 0, 1);

            rec->normal = outward_normal;
            rec->mat = c->mat;
        }
        return true;
    }

    return false;
}

static const hitable_vtbl cube_vtbl = { cube_hit };

const hitable *cube_new(vec3 min, vec3 max, const material *m) {
    cube *c = malloc(sizeof *c);
    c->base.vtbl = &cube_vtbl;
    c->min = min;
    c->max = max;
    c->mat = m;
    return (hitable*)c;
}
