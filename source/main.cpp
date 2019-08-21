#include "ppm.h"

#include "vec.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "camera.h"
#include "quick_random.h"

#include <limits>

#include "print.h"


// Ambiant light color computed based on the direction of the ray
vec3 ambiant_light(const Ray& ray){
    vec3 unit_direction = normalize(ray.direction);
    float unit_vertical = 0.5f + (unit_direction.y + 1.f);

    return (1.f - unit_vertical) * vec3(1.f, 1.f, 1.f)
        + unit_vertical * vec3(0.5f, 0.7f, 1.f);
}

template <typename T>
T clamp(const T& number, const T& lower, const T& upper) {
  return std::max(lower, std::min(number, upper));
}

static int scene_number_of_spheres;
static HitableList* scene;
static Material** scene_materials;
static Hitable** scene_spheres;

void create_test_scene(){
    scene_number_of_spheres = 5;

    scene_materials = new Material*[scene_number_of_spheres];
    scene_spheres = new Hitable*[scene_number_of_spheres];

    scene_materials[0] = new Lambertian(vec3(0.1f, 0.2f, 0.5f));
    scene_materials[1] = new Lambertian(vec3(0.8f, 0.8f, 0.f));
    scene_materials[2] = new Metal(vec3(0.8f, 0.6f, 0.2f), 0.f);
    scene_materials[3] = new Dielectric(1.5f);

    scene_spheres[0] = new Sphere(vec3(0.f, 0.f, -1.f), 0.5f, scene_materials[0]);
    scene_spheres[1] = new Sphere(vec3(0.f, -100.5f, -1.f), 100.f, scene_materials[1]);
    scene_spheres[2] = new Sphere(vec3(1.f, 0.f, -1.f), 0.5f, scene_materials[2]);
    scene_spheres[3] = new Sphere(vec3(-1.f, 0.f, -1.f), 0.5f, scene_materials[3]);
    scene_spheres[4] = new Sphere(vec3(-1.f, 0.f, -1.f), -0.45f, scene_materials[3]);

    scene = new HitableList(scene_spheres, 5);
}

void create_random_scene(){

    scene_number_of_spheres = 500;

    scene_materials = new Material*[scene_number_of_spheres];
    scene_spheres = new Hitable*[scene_number_of_spheres];

    scene_materials[0] = new Lambertian(vec3(0.5, 0.5, 0.5));
    scene_spheres[0] = new Sphere(vec3(0, -1000, 0), 1000, scene_materials[0]);

    int current_sphere = 1;

    for(int coordX = -11; coordX < 11; ++coordX){
        for(int coordY = -11; coordY < 11; ++coordY){
            vec3 sphere_center = vec3(coordX + 0.9 * random_normalized_positive(),
                                    0.2,
                                    coordY + 0.9 * random_normalized_positive());

            if(length(sphere_center - vec3(4, 0.2, 0)) > 0.9){

                float material_sample = random_normalized_positive();

                constexpr float threshold_diffuse = 0.8;
                constexpr float threshold_metal = 0.95;

                // Diffuse
                if(material_sample < threshold_diffuse){

                    scene_materials[current_sphere] = new Lambertian(
                            vec3(random_normalized_positive() * random_normalized_positive(),
                                random_normalized_positive() * random_normalized_positive(),
                                random_normalized_positive() * random_normalized_positive()));

                // Metal
                }else if(material_sample < threshold_metal){

                    scene_materials[current_sphere] = new Metal(
                            vec3(0.5 * (1 + random_normalized_positive()),
                                0.5 * (1 + random_normalized_positive()),
                                0.5 * (1 + random_normalized_positive())),
                            0.5 * random_normalized_positive());

                // Glass
                }else{
                    scene_materials[current_sphere] = new Dielectric(1.5);

                }

                scene_spheres[current_sphere] = new Sphere(sphere_center, 0.2, scene_materials[current_sphere]);
                ++current_sphere;
            }
        }
    }

    scene_materials[current_sphere] = new Dielectric(1.5);
    scene_spheres[current_sphere] = new Sphere(vec3(0, 1, 0), 1.0, scene_materials[current_sphere]);
    ++current_sphere;

    scene_materials[current_sphere] = new Lambertian(vec3(0.4, 0.2, 0.1));
    scene_spheres[current_sphere] = new Sphere(vec3(-4, 1, 0), 1.0, scene_materials[current_sphere]);
    ++current_sphere;

    scene_materials[current_sphere] = new Metal(vec3(0.7, 0.6, 0.5), 0.);
    scene_spheres[current_sphere] = new Sphere(vec3(4, 1, 0), 1.0, scene_materials[current_sphere]);
    ++current_sphere;

    scene = new HitableList(scene_spheres, current_sphere);
}

void delete_scene(){
    delete[] scene_materials;
    delete[] scene_spheres;
    delete scene;
}

int main(){

    int sizeX = 400;
    int sizeY = 200;
    vec3 pixel_data[sizeX * sizeY];

    // test_scene
    vec3 camera_position(3, 3, 2);
    vec3 focus_position(0, 0, -1);
    float aperture = 0.25f;

    // random_scene
    //vec3 camera_position(17.5f, 3.f, 4.f);
    //vec3 focus_position(0.f, 0.75f, 0.f);
    //float aperture = 0.25f;

    vec3 camera_up(0.f, 1.f, 0.f);
    float field_of_view = 20.f;
    float aspect_ratio = (float)sizeX / (float)sizeY;
    float focus_distance = length(focus_position - camera_position);

    Camera camera(camera_position, focus_position, camera_up, field_of_view, aspect_ratio, aperture, focus_distance);

    create_test_scene();
    //create_random_scene();
    Hitable* world = scene;

    constexpr int number_of_samples = 50;
    constexpr int max_bounce = 10;
    constexpr float bounce_hit_tolerance = 0.001;

    for(int row = 0; row != sizeY; ++row){
        for(int column = 0; column != sizeX; ++column){

            vec3 pixel_color;
            for(int sample = 0; sample != number_of_samples; ++sample){

                float u = (float)(column + random_normalized())
                        / (float)sizeX;
                float v = (float)(row + random_normalized())
                        / (float)sizeY;

                Ray ray = camera.ray(u, v);
                HitRecord record;

                if(world->hit(ray, 0.f, std::numeric_limits<float>::max(), record)){

                    // Ambiant-occlusion coloring
                    Ray subray = ray;
                    HitRecord subrecord = record;

                    int bounces = 0;

                    vec3 source_attenuation(1.f, 1.f, 1.f);

                    do{

                        ++bounces;

                        Ray scatter_ray;
                        vec3 scatter_attenuation;

                        if(subrecord.material->scatter(subray, subrecord, scatter_attenuation, scatter_ray) != RayType::None){
                            source_attenuation *= scatter_attenuation;
                            subray = scatter_ray;

                        // Bounce was not successful ie stop bouncing and nullify contribution
                        }else{
                            source_attenuation = vec3(0.f, 0.f, 0.f);
                            bounces = max_bounce;
                        }


                    }while(bounces < max_bounce
                            && world->hit(subray, 0.f + bounce_hit_tolerance, std::numeric_limits<float>::max(), subrecord));

                    pixel_color += source_attenuation * ambiant_light(ray);

                    // Normal-based coloring
                    //pixel_color += (record.normal + 1.f);

                }else{

                    pixel_color += ambiant_light(ray);

                }
            }
            pixel_color /= number_of_samples;

            const int pixel_index = row * sizeX + column;
            pixel_data[pixel_index] = pixel_color;
        }
    }

    // Free memory
    delete_scene();
    world = nullptr;

    // Gamma correction using gamma = 0.5 ie pow(i, 0.5) ie sqrt()
    for(int ipixel = 0; ipixel != sizeX * sizeY; ++ipixel){
        pixel_data[ipixel].x = std::sqrt(pixel_data[ipixel].x);
        pixel_data[ipixel].y = std::sqrt(pixel_data[ipixel].y);
        pixel_data[ipixel].z = std::sqrt(pixel_data[ipixel].z);
    }

    // Converting the floating point color to unsigned char
    unsigned char color_data[sizeX * sizeY * 3];
    for(int ipixel = 0; ipixel != sizeX * sizeY; ++ipixel){
        color_data[3 * ipixel + 0] = (unsigned char)clamp(pixel_data[ipixel].r * 255.99f, 0.f, 255.f);
        color_data[3 * ipixel + 1] = (unsigned char)clamp(pixel_data[ipixel].g * 255.99f, 0.f, 255.f);
        color_data[3 * ipixel + 2] = (unsigned char)clamp(pixel_data[ipixel].b * 255.99f, 0.f, 255.f);
    }

    writeP3("image.ppm", sizeX, sizeY, color_data);

    return 0;
}
