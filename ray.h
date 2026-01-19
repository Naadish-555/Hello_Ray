#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
	point3 ogn;	//origin
	vec3 dxn;	//direction

public:
	ray() = default;

	ray(const point3& origin, const vec3& direction) : ogn(origin), dxn(direction) {}

	const point3& origin() const { return ogn; }
	const vec3& direction() const { return dxn; }

	point3 at(double t) const
	{
		return ogn + t * dxn;
	}
};

#endif // !RAY_H
