#include <stdio.h>
#include <float.h>
#include <math.h>
#include <time.h>

#include "rng.h"
#include "camera.h"
#include "hitable_list.h"
#include "sphere.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "cube.h"

static const material *mat_sun = NULL;

static vec3 color(ray r, const hitable *world, int depth)
{
    hit_record rec;
    if (world->vtbl->hit(world, r, 0.001, DBL_MAX, &rec)) {
        if (rec.mat == mat_sun)
            return v3(5.0, 4.5, 3.0);

        ray  scattered;
        vec3 attenuation;
        if (depth < 50 &&
            rec.mat->vtbl->scatter(rec.mat, r, &rec,
                                   &attenuation, &scattered))
            return v3_mul(attenuation,
                          color(scattered, world, depth + 1));

        return v3(0,0,0);
    }
    return v3(0,0,0);
}

int main(void)
{
    const int nx = 720;
    const int ny = 720;
    const int ns = 720;             // foton per-pixel
    rng_seed(0xDEADBEEF);

    // materials
    const material *mat_ground    = lambertian_new(v3(0.9, 0.7, 0.3));
    const material *mat_ball     = dielectric_new    (1.5); // стекло
    //const material *mat_ball     = metal_new     (v3(0.8, 0.85, 0.88), 0.05); /*  металл */
    //const material *mat_ball      = lambertian_new(v3(0.4, 0.4, 0.4)); // - матовый материал
    mat_sun                       = lambertian_new(v3(1,1,1));
    const material *mat_star_red  = lambertian_new(v3(1.0, 0.1, 0.1));
    //vec3 cube_min = v3(-0.1, -0.1, -0.1);
    //vec3 cube_max = v3(0.1, 0.1, 0.1);
    //const material *mat_cube = dielectric_new(1.3); // или другой материал

    // object on scene
    const hitable *list[] = {
            sphere_new(v3( 0,-1000.5,-1), 1000.0, mat_ground),
            sphere_new(v3( 0,    0.0,-1),    0.6, mat_ball),
            //cube_new(cube_min, cube_max, mat_cube),
            sphere_new(v3( 4,    1.0,-3),    1.4, mat_sun),
            sphere_new(v3(-2,    1.2,-3),    1.0, mat_star_red)
    };
    hitable_list world =
            hitable_list_from(list, sizeof list / sizeof *list);

    // camera
    vec3 lookfrom = v3(-2, 0.8, 2);
    vec3 lookat   = v3(0,  0.0, -1);
    double dist_to_focus = v3_len(v3_sub(lookfrom, lookat));
    camera cam = camera_new(lookfrom, lookat, v3(0,1,0),
                            35.0, (double)nx/ny,
                            0.0, dist_to_focus);

    // progress bar
    setvbuf(stderr, NULL, _IONBF, 0);
    const int bar_w      = 40;
    const char *bar_full  =
            "########################################";
    const char *bar_empty =
            "                                        ";

    clock_t t_start = clock();

    printf("P3\n%d %d\n255\n", nx, ny);

    // render
    for (int j = ny - 1; j >= 0; --j) {

        int done      = ny - 1 - j;
        double ratio  = (double)done / ny;
        int filled    = (int)(bar_w * ratio);
        double pct    = ratio * 100.0;

        double elapsed = (double)(clock() - t_start) / CLOCKS_PER_SEC;

        fprintf(stderr,
                "\r[%.*s%.*s] %5.1f%% | %.1fs",
                filled, bar_full,
                bar_w - filled, bar_empty,
                pct,
                elapsed);

        for (int i = 0; i < nx; ++i) {

            vec3 col = v3(0,0,0);

            for (int s = 0; s < ns; ++s) {
                double u = (i + rng_double()) / nx;
                double v = (j + rng_double()) / ny;
                ray r = camera_get_ray(&cam, u, v);
                col = v3_add(col, color(r, (hitable *)&world, 0));
            }

            col = v3_div(col, ns);
            col = v3_sqrt(col);               // γ-correction

            int ir = (int)(255.99 * col.x);
            int ig = (int)(255.99 * col.y);
            int ib = (int)(255.99 * col.z);

            printf("%d %d %d\n", ir, ig, ib);
        }
    }

    fputc('\n', stderr);

    return 0;
}
