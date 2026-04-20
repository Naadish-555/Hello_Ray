#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
//#include <cstdlib>
#include <random>
#include <limits>
#include <memory>


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589793285;

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

inline double random_double()
{
	//returns a random real in (0,1]
	//return std::rand() / (RAND_MAX + 1.0);

	//modern C++ random generator
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double random_double(double min, double max)
{
	//returns a random real in [min,max)
	return min + (max - min) * random_double();
}



#include "interval.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif // !RTWEEKEND_H

