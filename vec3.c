#include "vec3.h"

vec3 v3_add(vec3 a, vec3 b) { return v3(a.x+b.x, a.y+b.y, a.z+b.z); }
vec3 v3_sub(vec3 a, vec3 b) { return v3(a.x-b.x, a.y-b.y, a.z-b.z); }
vec3 v3_mul(vec3 a, vec3 b) { return v3(a.x*b.x, a.y*b.y, a.z*b.z); }
vec3 v3_scale(vec3 v, double k){ return v3(v.x*k, v.y*k, v.z*k); }
vec3 v3_div(vec3 v, double k)  { return v3_scale(v, 1.0/k); }
vec3 v3_sqrt(vec3 v){ return v3( sqrt(v.x), sqrt(v.y), sqrt(v.z) ); }

double v3_dot(vec3 a, vec3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }

vec3 v3_cross(vec3 a, vec3 b){
    return v3(a.y*b.z - a.z*b.y,
              a.z*b.x - a.x*b.z,
              a.x*b.y - a.y*b.x);
}

double v3_len(vec3 v){ return sqrt(v3_dot(v,v)); }
vec3   v3_unit(vec3 v){ return v3_div(v, v3_len(v)); }