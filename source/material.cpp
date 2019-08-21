#include "material.h"

#include <cmath>

vec3 reflect_ray(const vec3& ray, const vec3& normal){
    return ray - 2.f * dot(ray, normal) * normal;
}

bool refract_ray(const vec3& ray_in, const vec3& normal, const float nin_over_nout, vec3& ray_out){
    vec3 unit_ray_in = normalize(ray_in);
    float cos_in = dot(unit_ray_in, normal);
    float radicande_cos_out = 1.f - nin_over_nout * nin_over_nout * (1.f - cos_in * cos_in);

    if(radicande_cos_out < 0){
        return false;
    }

    ray_out = nin_over_nout * (unit_ray_in - normal * cos_in) - normal * std::sqrt(radicande_cos_out);

    return true;
}

float specular_reflection_schlick(const float cos_in,
        const float refraction_index_in,
        const float refraction_index_out){

    float specular_base = (refraction_index_in - refraction_index_out) / (refraction_index_in + refraction_index_out);
    specular_base = specular_base * specular_base;

    const float temp_term = (1.f - cos_in);
    const float temp_term_pow5 = temp_term * temp_term * temp_term * temp_term * temp_term;

    return specular_base + (1.f - specular_base) * temp_term_pow5;
}

Lambertian::Lambertian(const vec3& ialbedo)
: albedo(ialbedo){
}

RayType Lambertian::scatter(const Ray& ray_in, const HitRecord& record,
                        vec3& attenuation, Ray& ray_out) const{

    // Parameter unused but the function signature needs to be the same as for the parent
    (void)ray_in;

    ray_out.origin = record.point;
    ray_out.direction = record.normal + random_point_inside_sphere();
    attenuation = albedo;

    return RayType::Secondary;
};

Metal::Metal(const vec3& ialbedo, const float ifuziness)
: albedo(ialbedo), fuziness(ifuziness){
}

RayType Metal::scatter(const Ray& ray_in, const HitRecord& record, vec3& attenuation, Ray& ray_out) const{

    ray_out.origin = record.point;
    ray_out.direction = reflect_ray(normalize(ray_in.direction), record.normal)
                        + fuziness * random_point_inside_sphere();
    attenuation = albedo;

    // Check that the secondary ray is in the same direction as the surface normal
    if(dot(ray_out.direction, record.normal) > 0.f){
        return RayType::Reflected;
    }
    return RayType::None;
}

Dielectric::Dielectric(const float irefraction_index)
: refraction_index(irefraction_index){
}

RayType Dielectric::scatter(const Ray& ray_in, const HitRecord& record, vec3& attenuation, Ray& ray_out) const{

    constexpr float refraction_index_other = 1.f; // Air

    float refraction_index_ratio; // ray_in_material / ray_out_material

    // Computing the refraction_normal to be in the direction of the refracted ray
    vec3 refraction_normal;
    float specular_probability;

    // ray_in from inside the material
    if(dot(ray_in.direction, record.normal) > 0.f){
        refraction_normal = - record.normal;
        refraction_index_ratio = refraction_index / refraction_index_other;

        float specular_cosine = dot(normalize(ray_in.direction), record.normal);
        specular_probability = specular_reflection_schlick(specular_cosine, refraction_index, refraction_index_other);

    // ray_in from outside the material
    }else{
        refraction_normal = record.normal;
        refraction_index_ratio = refraction_index_other / refraction_index;

        float specular_cosine = - dot(normalize(ray_in.direction), record.normal);
        specular_probability = specular_reflection_schlick(specular_cosine, refraction_index_other, refraction_index);
    }

    attenuation = vec3(1.f, 1.f, 1.f);

    // The direction of the reflected ray

    ray_out.origin = record.point;
    if(!refract_ray(ray_in.direction, refraction_normal, refraction_index_ratio, ray_out.direction)){
        ray_out.direction = reflect_ray(ray_in.direction, record.normal);

        // Not (dot(ray_out.direction, record.normal) > 0.f) because it does not authorize 'inverted' spheres

        return RayType::Reflected;

    }else{

        if(random_normalized_positive() < specular_probability){
            ray_out.direction = reflect_ray(ray_in.direction, record.normal);

            return RayType::Reflected;
        }
    }

    return RayType::Refracted;

}
