#include "plane.h"

namespace film {

namespace hitable {

bool plane::hit(const math::ray& ray, double& t_min, hit_record& rec) const {
  double t = (point - ray.origin) * normal / (ray.direction * normal);
 
  if(t > 0.001) {
    t_min = t;
    rec.normal = normal;
    rec.hit_point = ray.origin + t * ray.direction;

    return true;
  }

  return false;
}

}

}
