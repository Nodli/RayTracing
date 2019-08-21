#ifndef H_HITABLE
#define H_HITABLE

#include "ray.h"

struct Material;

struct HitRecord{
    float ray_parameter;
    vec3 point;
    vec3 normal;

    Material* material;
};

struct Hitable{

// Declaration and definition of ~Hitable are mandatory even if they are made
// pure virtual
// This is to avoid undefined behavior cf. following error message
//
// warning: deleting object of abstract class type ‘Hitable’ which has
//          non-virtual destructor will cause undefined behavior
//          [-Wdelete-non-virtual-dtor]
//
// code:    Hitable* world = new Sphere;
//          delete world;

    virtual ~Hitable() = 0;

    virtual bool hit(const Ray& ray,
            const float min_param, const float max_param,
            HitRecord& record) const = 0;
};

struct Sphere : Hitable{

    Sphere();
    Sphere(const vec3& icenter, const float iradius, Material* const imaterial);
    virtual ~Sphere();

    virtual bool hit(const Ray& ray,
            const float min_param, const float max_param,
            HitRecord& record) const;

    vec3 center;
    float radius;
    Material* material;
};

struct HitableList : Hitable{

    HitableList(Hitable** iroot, int icount);
    virtual ~HitableList();

    virtual bool hit(const Ray& ray,
            float min_param, float max_param,
            HitRecord& record) const;

    Hitable** root = nullptr;
    int count = 0;
};

#endif
