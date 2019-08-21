#include "camera.h"
#include "quick_random.h"

Camera::Camera(const vec3& look_from, const vec3& look_at, const vec3& up,
        const float vertical_fov_deg, const float aspect_ratio,
        const float ilens_aperture_radius, const float focal_length){

    camera_basis_depth = normalize(look_from - look_at);
    camera_basis_horizontal = normalize(cross(up, camera_basis_depth));
    camera_basis_vertical = cross(camera_basis_depth, camera_basis_horizontal);

    const float vertical_fov_rad = vertical_fov_deg * (M_PI / 180.f);
    const float half_height = tan(vertical_fov_rad / 2.f);
    const float half_width = half_height * aspect_ratio;

    origin = look_from;
    top_left_corner = origin
        - half_width * focal_length * camera_basis_horizontal
        + half_height * focal_length * camera_basis_vertical
        - focal_length * camera_basis_depth;
    horizontal = 2.f * half_width * focal_length * camera_basis_horizontal;
    vertical = - 2.f * half_height * focal_length * camera_basis_vertical;

    lens_aperture_radius = ilens_aperture_radius;
}

Ray Camera::ray(float u, float v){

    // Synthetic Aperture Imaging / Photography
    // Averaging multiple images around the point to focus
    // http://users.eecs.northwestern.edu/~ollie/eecs395/HW6/HW6.htm

    // ->   The ray origin is randomly displaced to simulate multiple viewpoints
    // ->   The ray direction is corrected by the same amount to target the same
    //      point from the focus plane

    vec3 random_displacement(lens_aperture_radius * random_normalized(),
            lens_aperture_radius * random_normalized(),
            0.f);

    vec3 camera_offset = camera_basis_horizontal * random_displacement
        + camera_basis_horizontal * random_displacement;

    return Ray(origin + camera_offset,
            top_left_corner + u * horizontal + v * vertical - origin - camera_offset);
}
