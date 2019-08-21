#include "vec.h"

// ---- vec2 ---- //

vec2::vec2()
: x(0.f), y(0.f){
}

vec2::vec2(const float f)
: x(f), y(f){
}

vec2::vec2(const float ix, const float iy)
: x(ix), y(iy){
}

// ---- vec3 ---- //

vec3::vec3()
: x(0.f), y(0.f), z(0.f){
}

vec3::vec3(const float f)
: x(f), y(f), z(f){
}

vec3::vec3(const float ix, const float iy, const float iz)
: x(ix), y(iy), z(iz){
}
