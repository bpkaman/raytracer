#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility
inline double degrees_to_radians(double degrees) { return pi * degrees / 180.0; }
inline double radians_to_degrees(double radians) { return 180.0 * radians / pi; }

inline double random_double()
{
    // returns a random real 0->1
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    // returns random double between min and max
    return min + (max-min) * random_double();
}

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif