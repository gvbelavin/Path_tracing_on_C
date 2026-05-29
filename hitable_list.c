#include "hitable_list.h"

static bool hitable_list_hit(const void *self,
                             ray r,
                             double t_min, double t_max,
                             hit_record *rec)
{
    const hitable_list *list = self;
    hit_record temp_rec;
    bool  hit_anything   = false;
    double closest_sofar = t_max;

    for (size_t i = 0; i < list->count; ++i) {
        const hitable *obj = list->objects[i];
        if (obj->vtbl->hit(obj, r, t_min, closest_sofar, &temp_rec)) {
            hit_anything   = true;
            closest_sofar  = temp_rec.t;
            *rec           = temp_rec;
        }
    }
    return hit_anything;
}

static const hitable_vtbl list_vtbl = { hitable_list_hit };

hitable_list hitable_list_from(const hitable **objs, size_t count)
{
    hitable_list l;
    l.base.vtbl = &list_vtbl;
    l.objects   = objs;
    l.count     = count;
    return l;
}