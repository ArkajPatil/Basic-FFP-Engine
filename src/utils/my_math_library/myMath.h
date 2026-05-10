#ifndef MYMATH_H
#define MYMATH_H

#include <math.h> // for 3d maths
#define PI 3.14159265359f

// vectors declarations
typedef struct {
    float x, y, z;
} vec3;

typedef struct {
    float w, x, y, z;
} vec4;

// functions declarations
vec3 scale(vec3 v, float s);
vec3 add(vec3 v1, vec3 v2);
vec3 subtract(vec3 v1, vec3 v2);
vec3 cross(vec3 v1, vec3 v2);  // return the cross product vector
float magnitudeOfVec3(vec3 vec);
vec3 normalize(vec3 vec);  // returns a unit vector in given vector direction


#endif

