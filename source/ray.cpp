#include "ray.h"

Ray::Ray(){
}

Ray::Ray(const vec3& iorigin, const vec3& idirection)
: origin(iorigin), direction(idirection){
}

vec3 Ray::at(const float t) const{
    return origin + t * direction;
}
