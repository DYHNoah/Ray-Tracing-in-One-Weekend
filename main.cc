#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

double hit_sphere(const vec3& center, double radius, const ray& r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius*radius;
  auto discriminant = half_b*half_b - a*c;
  
  if (discriminant < 0) {
      return -1.0;
  } else {
      return (-half_b - sqrt(discriminant) ) / a;
  }
}
    
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
	return 0.5 * (rec.normal + vec3(1, 1, 1));
    }
    vec3 unit_direction = unit_vector (r.direction ());
    auto t = 0.5*(unit_direction.y () + 1.0);
    return (1.0-t)*vec3 (1.0, 1.0, 1.0) + t*vec3 (0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 200;
    const int image_height = 100;
    const int samples_per_pixel = 100;

    // Camera
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(vec3(0, 100.5, -1), 100));
    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));
    camera cam;
//    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));
    // Render

//    std::cerr << infinity << std::endl;
    
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
	    vec3 color(0, 0, 0);
	    for (int s = 0; s < samples_per_pixel; ++s)  {
		auto u = (i + random_double()) / image_width;
		auto v = (j + random_double()) / image_height;
		ray r = cam.get_ray(u, v);
		color += ray_color(r, world);
	    }
	    color.write_color(std::cout, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
