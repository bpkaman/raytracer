#include <iostream>
#include "color.h"
#include "ray.h"
#include "vec3.h"

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

color ray_color(const ray& r) {
    double t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
    // Setup our image dimensions
    const double aspect = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect);

    // putting these here to prevent reallocation during the image dump
    const double _width = static_cast<double>(image_width) - 1.0;
    const double _height = static_cast<double>(image_height) - 1.0;

    // Setup the camera
    double viewport_height = 2.0;
    double viewport_width = aspect * viewport_height;
    double focal_length = 1.0;
    point3 origin = point3(0.0, 0.0, 0.0);
    vec3 horizontal = vec3(viewport_width, 0.0, 0.0);
    vec3 vertical = vec3(0.0, viewport_height, 0.0);
    point3 corner_ll = origin - (horizontal / 2.0) - (vertical / 2.0) - vec3(0.0, 0.0, focal_length);


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
            u = static_cast<double>(i) / _width;
            v = static_cast<double>(j) / _height;
            r = ray(origin, corner_ll + u * horizontal + v * vertical - origin);
            pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);

        }
    }

    std::cerr << std::endl << "Done." << std::endl;
}