cmake_minimum_required(VERSION 3.27)
project(Raytracing C)

set(CMAKE_C_STANDARD 11)

add_executable(Raytracing main.c
        vec3.h
        vec3.c
        ray.h
        hit.h
        material.h
        lambertian.c
        sphere.h
        sphere.c
        camera.h
        rng.h
        hitable_list.h
        hitable_list.c
        camera.c
        metal.h
        metal.c
        dielectric.h
        dielectic.c
        lambertian.h
        cube.h
        cube.c
)
