#ifndef H_CAMERA
#define H_CAMERA

#include "ray.h"

struct Camera{

    Camera(const vec3& look_from, const vec3& look_at, const vec3& up,
            const float vertical_fov_deg, const float aspect_ratio,
            const float lens_aperture_radius, const float focal_length);

    Ray ray(float u, float v);

    vec3 origin;
    vec3 top_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 camera_basis_horizontal, camera_basis_vertical, camera_basis_depth; // u, v, w
    float lens_aperture_radius;
};

#endif
