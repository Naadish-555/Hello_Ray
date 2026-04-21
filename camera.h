#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera
{
public:

	//rendered img setup
	double	aspect_ratio = 1.0;
	int		img_width = 100;
	int		sample_per_pixel = 10; //count of samples for each pixel
	int		max_depth = 10;			//max number of ray bounces into scene
	


	void render(const hittable& world)
	{
		intialize();

		std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";

		for (int j = 0; j < img_height; j++)
		{
			std::clog << "\rScanlines remaining : " << (img_height - j) << " " << std::flush;
			for (int i = 0; i < img_width; i++)
			{
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < sample_per_pixel; sample++)
				{
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				write_color(std::cout, pixel_samples_scale * pixel_color);
			}
		}

		std::clog << "\r Done........................... \n";
	}

private:

	int		img_height;
	double	pixel_samples_scale;	//color scale factor for a sum of pixel samples
	point3	center;					// Camera center
	point3	pixel00_loc;
	vec3	pixel_delta_u;
	vec3	pixel_delta_v;

	void intialize()
	{


		//calculating img height and ensuring its atleast 1
		img_height = int(img_width / aspect_ratio);
		img_height = (img_height < 1) ? 1 : img_height;


		pixel_samples_scale = 1.0 / sample_per_pixel;

		//Camera
		center = point3(0, 0, 0);

		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (double(img_width) / img_height);

		//vectors across the horizontal and down the vertical viewport edges
		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		//horizontal and vertical delta vectors from pixel to pixel
		pixel_delta_u = viewport_u / img_width;
		pixel_delta_v = viewport_v / img_height;

		//location of upper left pixel
		auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		/*std::cout << img_width << " , " << img_height << std::endl;*/
	}

	color ray_color(const ray& r,int depth, const hittable& world) const
	{
		// if exceeded the ray bounce limit, no more light is gathered.
		if (depth <= 0)
			return color(0, 0, 0);

		hit_record rec;
		//shadow acne fix , ignore hits that are very close to the calculated intersection point
		if (world.hit(r, interval(0.001, infinity), rec))
		{
			///equally bouncing of the light in all dxns from normal
			//vec3 direction = random_on_hemisphere(rec.normal);

			///lmabertian distribution = reflected ray most likely to scatter in a dxn near surface normal and less likely to scatter in directions away from the normal.
			//vec3 direction = rec.normal + random_unit_vector();

			ray scattered;
			color attenuation;
			if (rec.mat->scatter(r, rec, attenuation, scattered))
				return attenuation * ray_color(scattered, depth - 1, world);
			return color(0, 0, 0);

			//return 0.15 * ray_color(ray(rec.p, direction), depth - 1, world);
		}

		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

	ray get_ray(int i, int j) const
	{ 
		// Construct a camera ray originating from the origin and directed at
		//  randomly sampled point around the pixel location i, j.

		auto offset = sample_square();
		auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

		auto ray_origin = center;
		auto ray_direction = pixel_sample - ray_origin;

		return ray(ray_origin, ray_direction);
	}

	vec3 sample_square() const
	{
		//returns a random point in unit square in range [-.5,-.5]-[+.5,+.5]
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}
};


#endif // !CAMERA_H
