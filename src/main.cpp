#include <iostream>
#include <vec3.h>
#include <color.h>

int main()
{
    const int image_width = 256, image_height = 256;
    const double _width = static_cast<double>(image_width) - 1.0;
    const double _height = static_cast<double>(image_height) - 1.0;

    std::cout << "P3" << std::endl;
    std::cout << image_width << " " << image_height <<  std::endl << "255" << std::endl;

    int i, j;
    double r, g, b, ir, ig, ib;


    for (j = image_height; j >= 0; --j)
    {
        for (i = 0; i < image_width; ++i)
        {
            std::cerr << std::endl << "Scanlines remaining: " << j << ' ' << std::flush;
            r = static_cast<double>(i) / _width;
            g = static_cast<double>(j) / _height;
            b = 0.0;

            ir = static_cast<int>(255.999 * r);
            ig = static_cast<int>(255.999 * g);
            ib = 0.0;

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

    std::cerr << std::endl << "Done." << std::endl;
}