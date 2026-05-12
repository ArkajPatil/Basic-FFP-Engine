#include "myMath.h"

// functions body
vec3 scale(vec3 v, float s)
{
    return vec3{
        v.x * s,
        v.y * s,
        v.z * s
    };
}

vec3 add(vec3 v1, vec3 v2)
{
    vec3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

vec3 subtract(vec3 v1, vec3 v2)
{
    vec3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

vec3 cross(vec3 v1, vec3 v2)
{
    vec3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

float magnitudeOfVec3(vec3 vec)
{
    return sqrtf((vec.x*vec.x) + (vec.y*vec.y) + (vec.z*vec.z));
}

vec3 normalize(vec3 vec)
{
    float len = magnitudeOfVec3(vec);
    if(len == 0.0f) 
    {
        return vec3{0.0f, 0.0f, 0.0f};
    }

    vec3 result;
    result.x = vec.x / len;
    result.y = vec.y / len;
    result.z = vec.z / len;
    return result;
}

