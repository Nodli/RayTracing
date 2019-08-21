#ifndef H_QUICK_RANDOM
#define H_QUICK_RANDOM

#include "vec.h"

float random_normalized();
float random_normalized_positive();

// TODO : Implement something cleaner than rejection sampling
// http://6degreesoffreedom.co/circle-random-sampling/
vec3 random_point_inside_sphere();

#endif
