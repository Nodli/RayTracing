#ifndef H_RAY
#define H_RAY

#include "vec.h"

struct Ray{

    Ray();
    Ray(const vec3& iorigin, const vec3& idirection);

    vec3 at(const float t) const;

    vec3 origin;
    vec3 direction;
};

#endif
