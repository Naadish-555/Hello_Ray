#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


int main()
{



	//world

	hittable_list world;
	
	world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(std::make_shared<sphere>(point3(0, -3, -1.0), 3));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.img_width = 400;


	cam.render(world);


	

	return 0;
}