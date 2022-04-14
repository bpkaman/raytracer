#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

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

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif