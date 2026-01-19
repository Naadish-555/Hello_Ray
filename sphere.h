#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
	point3 center;
	double radius;

public:
	sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override
	{
		vec3 oc = center - r.origin();
		auto a = r.direction().length_squared();
		//auto b = -2.0 * dot(r.direction(), oc);
		auto h = dot(r.direction(), oc);
		auto c = oc.length_squared() - radius * radius;

		auto discriminant = h * h - a * c;
		if (discriminant < 0)
			return false;
		
		auto sqrtd = std::sqrt(discriminant);

		//find nearest root that lies in acceptable range
		auto root = (h - sqrtd) / a;					//first checking lower root
		if (root <= ray_t.min || ray_t.max <= root)
		{
			root = (h + sqrtd) / a;						//if first root not in range then check the larger root
			if (root <= ray_t.min || ray_t.max <= root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		
		return true;

	}
};



#endif // !SPHERE_H
