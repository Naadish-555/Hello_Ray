#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589793285;

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

#include "interval.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif // !RTWEEKEND_H

