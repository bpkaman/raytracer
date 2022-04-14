#include <iostream>
#include "color.h"
#include "hittable.h"
#include "sphere.h"
#include "rtweekend.h"
#include "camera.h"


double hit_sphere(const point3& center, double radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0.0) { return -1.0; }
    else { return (-half_b - sqrt(discriminant) ) / (a); }
}

color ray_color(const ray& r, const ShapeList& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Setup our image dimensions
    const double aspect = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect);
    const int samples_per_pixel = 100;

    // putting these here to prevent reallocation during the image dump
    const double _width = static_cast<double>(image_width) - 1.0;
    const double _height = static_cast<double>(image_height) - 1.0;

    // World
    ShapeList world;
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // Setup the camera
    camera cam;


    // Render the image into the .ppm file
    std::cout << "P3" << std::endl;
    std::cout << image_width << " " << image_height <<  std::endl << "255" << std::endl;

    int i, j;
    double u, v;
    ray r;
    color pixel_color;
    for (j = image_height; j >= 0; --j)
    {
        // dispaly a progress bar for each row complete
        std::cerr << std::endl << "Scanlines remaining: " << j << ' ' << std::flush;
        for (i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s=0; s < samples_per_pixel; ++s)
            {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << std::endl << "Done." << std::endl;
}