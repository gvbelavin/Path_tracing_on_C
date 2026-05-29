#ifndef RNG_H
#define RNG_H

#include <stdlib.h>
#include <math.h>
#include "vec3.h"

static inline void rng_seed(unsigned long seed)
{
#if defined(__unix__) || defined(__APPLE__)          /* POSIX */
    srand48(seed);
#else
    srand((unsigned int)seed);
#endif
}

static inline double rng_double(void)
{
#if defined(__unix__) || defined(__APPLE__)          /* есть drand48 */
    return drand48();
#else
    return (double)rand() / ((double)RAND_MAX + 1.0);
#endif
}

static inline vec3 rng_in_unit_sphere(void)
{
    vec3 p;
    do {
        p = v3_sub(v3_scale(v3(rng_double(), rng_double(), rng_double()), 2.0),
                   v3(1, 1, 1));
    } while (v3_dot(p, p) >= 1.0);
    return p;
}

static inline vec3 rng_in_unit_disk(void)
{
    vec3 p;
    do {
        p = v3_sub(v3_scale(v3(rng_double(), rng_double(), 0.0), 2.0),
                   v3(1, 1, 0));
    } while (v3_dot(p, p) >= 1.0);
    return p;
}

#endif
