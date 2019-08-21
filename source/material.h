#ifndef H_MATERIAL
#define H_MATERIAL

#include "quick_random.h"
#include "hitable.h"

vec3 reflect_ray(const vec3& ray, const vec3& normal);
bool refract_ray(const vec3& ray_in, const vec3& normal, const float nin_over_nout, vec3& ray_out);
float specular_reflection_schlick(const float cos_in, const float refraction_index_in, const float refraction_index_out);

// TODO : Put refraction_index in Material and use this in refarct via record.material

enum struct RayType {None = 0, Secondary = 1, Reflected = 2, Refracted = 3};

struct Material{
    virtual RayType scatter(const Ray& ray_in, const HitRecord& record, vec3& attenuation, Ray& ray_out) const = 0;
};

struct Lambertian : Material{

    Lambertian(const vec3& ialbedo);

    virtual RayType scatter(const Ray& ray_in, const HitRecord& record, vec3& attenuation, Ray& ray_out) const;

    vec3 albedo;
};

struct Metal : Material{

    Metal(const vec3& ialbedo, const float fuziness);

    virtual RayType scatter(const Ray& ray_in, const HitRecord& record, vec3& attenuation, Ray& ray_out) const;

    vec3 albedo;
    float fuziness;
};

struct Dielectric : Material{

    Dielectric(const float irefraction_index);

    virtual RayType scatter(const Ray& ray_in, const HitRecord& record, vec3& attenuation, Ray& ray_out) const;

    float refraction_index;
};

#endif
