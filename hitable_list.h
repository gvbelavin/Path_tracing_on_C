#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include <stddef.h>
#include "hit.h"

typedef struct {
    hitable base;
    const hitable **objects;
    size_t           count;
} hitable_list;

hitable_list hitable_list_from(const hitable **objs,
                               size_t count);
#endif