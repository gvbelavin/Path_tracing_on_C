#ifndef VEC3_H
#define VEC3_H
#include <math.h>

typedef struct { double x, y, z; } vec3;

static inline vec3 v3(double x, double y, double z) { return (vec3){x, y, z}; }

vec3  v3_add(vec3 a, vec3 b);
vec3  v3_sub(vec3 a, vec3 b);
vec3  v3_mul(vec3 a, vec3 b);
vec3  v3_scale(vec3 v, double k);
vec3  v3_div(vec3 v, double k);
vec3  v3_sqrt(vec3 v);

double v3_dot(vec3 a, vec3 b);
vec3   v3_cross(vec3 a, vec3 b);
double v3_len(vec3 v);
vec3   v3_unit(vec3 v);

#endif
