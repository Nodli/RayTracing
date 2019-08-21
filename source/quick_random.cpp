#include "quick_random.h"

#include <random>

thread_local std::mt19937 material_generator;

float random_normalized(){
    std::uniform_real_distribution<float> distribution(-1.f, 1.f);

    return distribution(material_generator);
}

float random_normalized_positive(){
    std::uniform_real_distribution<float> distribution(0.f, 1.f);

    return distribution(material_generator);
}

vec3 random_point_inside_sphere(){

    // Rejection sampling
    vec3 point;
    std::uniform_real_distribution<float> distribution(-1.f, 1.f);
    do{
        point.x = distribution(material_generator);
        point.y = distribution(material_generator);
        point.z = distribution(material_generator);
    }while(sqlength(point) > 1.f);

    return point;
}


