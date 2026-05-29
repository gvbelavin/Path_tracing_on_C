#include "camera.h"
#include <math.h>

camera camera_new(vec3 lookfrom, vec3 lookat, vec3 vup,
                  double vfov_deg, double aspect,
                  double aperture, double focus_dist)
{
    camera cam;
    cam.lens_radius = aperture * 0.5;

    double theta       = vfov_deg * M_PI / 180.0;
    double half_height = tan(theta * 0.5);
    double half_width  = aspect * half_height;

    cam.origin = lookfrom;

    cam.w = v3_unit( v3_sub(lookfrom, lookat) );
    cam.u = v3_unit( v3_cross(vup, cam.w) );
    cam.v = v3_cross(cam.w, cam.u);

    cam.lower_left = v3_sub(
            v3_sub(
                    v3_sub(cam.origin,
                           v3_scale(cam.u, half_width  * focus_dist)),
                    v3_scale(cam.v, half_height * focus_dist)),
            v3_scale(cam.w, focus_dist));

    cam.horizontal = v3_scale(cam.u, 2.0 * half_width  * focus_dist);
    cam.vertical   = v3_scale(cam.v, 2.0 * half_height * focus_dist);

    return cam;
}

ray camera_get_ray(const camera *c, double s, double t)
{
    vec3 rd = v3_scale(rng_in_unit_disk(), c->lens_radius);
    vec3 offset = v3_add( v3_scale(c->u, rd.x),
                          v3_scale(c->v, rd.y) );

    vec3 dir = v3_sub(
            v3_add( v3_add(c->lower_left,
                           v3_scale(c->horizontal, s)),
                    v3_scale(c->vertical,   t)),
            v3_add(c->origin, offset));

    return (ray){ v3_add(c->origin, offset), dir };
}
