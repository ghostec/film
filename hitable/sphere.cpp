#include <cmath>
#include "sphere.h"

namespace film {

namespace hitable {

sphere::sphere() : center(math::point3()), radius(85.0) {}

sphere::sphere(const math::point3& c, const double r) : center(c), radius(r) {}

bool sphere::hit(const math::ray& ray, double& t_min, hit_record& rec) const {
  double t;
  math::vec3 temp = ray.origin - center;
  double a = ray.direction * ray.direction;
  double b = 2.0 * temp * ray.direction;
  double c = temp * temp - radius * radius;
  double disc = b * b - 4.0 * a * c;

  if(disc < 0.0) return false;

  double e = sqrt(disc);
  double denom = 2.0 * a;
  t = (-b - e) / denom;

  if(t > 0.001) {
    t_min = t;
    rec.normal = (temp + t * ray.direction) / radius;
    rec.hit_point = ray.origin + t * ray.direction;
    rec.color = color;
    return true;
  }

  t = (-b + e) / denom;

  if(t > 0.001) {
    t_min = t;
    rec.normal = (temp + t * ray.direction) / radius;
    rec.hit_point = ray.origin + t * ray.direction;
    rec.color = color;
    return true;
  }

  return false;
}

}

}

