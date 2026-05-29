#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"
#include "rng.h"

typedef struct {
    vec3 origin, lower_left, horizontal, vertical;
    vec3 u,v,w;
    double lens_radius;
} camera;

camera camera_new(vec3 lookfrom, vec3 lookat, vec3 vup,
                  double vfov, double aspect,
                  double aperture, double focus_dist);

ray camera_get_ray(const camera *c, double s, double t);

#endif