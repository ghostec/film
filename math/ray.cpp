#include "ray.h"

namespace film {

namespace math {

ray::ray() : origin(point3()), direction(vec3()) {}
ray::ray(const point3& _origin, const vec3& _direction) : origin(_origin), direction(_direction) {}
ray::ray(const ray& _ray) : origin(_ray.origin), direction(_ray.direction) {}

ray::~ray() {}

ray& ray::operator=(const ray& rhs) {
  if(this == &rhs) return *this;

  origin = rhs.origin; direction = rhs.direction;
  
  return *this;
}

}

}
