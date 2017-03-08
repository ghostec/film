#include <cmath>

#include "sphere.h"

namespace film {
Sphere::Sphere(point3 center, float radius)
    : Hitable(hitable_t::SPHERE), center(center), radius(radius) {}
Sphere::~Sphere() {}

HitRecord Sphere::hit(const ray& ray, float t_min, float t_max) const {
  vec3 oc = ray.origin - center;
  float a = ray.direction * ray.direction;
  float b = 2.0 * (oc * ray.direction);
  float c = (oc * oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;

  if (discriminant <= 0.0001) return HitRecord{.hit = false};

  float temp = (-b - sqrt(discriminant)) / a;
  if (temp < t_max && temp > t_min) return hit_record_from_parameter(ray, temp);

  temp = (-b + sqrt(discriminant)) / a;
  if (temp < t_max && temp > t_min) return hit_record_from_parameter(ray, temp);

  return HitRecord{.hit = false};
}

HitRecord Sphere::hit_record_from_parameter(const ray& ray, float t) const {
  const auto p = ray.point_at_parameter(t);

  return HitRecord{
      .hit = true, .t = t, .point = p, .normal = (p - center) / radius};
}
}
