#include "hitable.h"

Hitable::~Hitable(){
}

Sphere::Sphere(){
}

Sphere::Sphere(const vec3& icenter, const float iradius, Material* const imaterial)
: center(icenter), radius(iradius), material(imaterial){
}

Sphere::~Sphere(){
}

bool Sphere::hit(const Ray& ray, const float min_param, const float max_param, HitRecord& record) const{
    vec3 origin_to_origin = ray.origin - center;

    // Searching a real solution for the quadratic equation
    float A = dot(ray.direction, ray.direction);
    float B = dot(origin_to_origin, ray.direction);
    float C = dot(origin_to_origin, origin_to_origin) - radius * radius;
    float D = B * B - A * C;

    // Without simplifications
    // float B = 2.f * dot(ray.direction, origin_to_origin);
    // float D = B * B - 4.f * A * C;
    // float parameter = (- B - std::sqrt(D)) / 2.f * A;

    if(D == 0){
        float parameter = - B / A;
        if(parameter < max_param && parameter > min_param){
            record.ray_parameter = - B / A;
            record.point = ray.at(record.ray_parameter);
            record.normal = (record.point - center) / radius;
            record.material = material;
            return true;
        }

    }else if(D > 0){
        float parameter = (- B - std::sqrt(D)) / A;
        if(parameter < max_param && parameter > min_param){
            record.ray_parameter = parameter;
            record.point = ray.at(parameter);
            record.normal = (record.point - center) / radius;
            record.material = material;
            return true;
        }

        parameter = (- B + std::sqrt(D)) / A;
        if(parameter < max_param && parameter > min_param){
            record.ray_parameter = parameter;
            record.point = ray.at(parameter);
            record.normal = (record.point - center) / radius;
            record.material = material;
            return true;
        }
    }

    return false;
}

HitableList::HitableList(Hitable** iroot, int icount)
: root(iroot), count(icount){
}

HitableList::~HitableList(){
}

bool HitableList::hit(const Ray& ray, const float min_param, const float max_param, HitRecord& record) const{

    bool hit = false;
    record.ray_parameter = max_param;

    for(int ihitable = 0; ihitable != count; ++ihitable){

        hit = hit | root[ihitable]->hit(ray, min_param, record.ray_parameter, record);

        //  The value of /record.ray_parameter/ is not updated when using a
        //  logical || instead of a bitwise |
        //  This is because logical operators || and && are allowed to
        //  short-circuit when the result is already known ie when /hit/ is true

        // hit = hit || root[ihitable]->hit(ray, min_param, record.ray_parameter, record);

    }

    return hit;
}
