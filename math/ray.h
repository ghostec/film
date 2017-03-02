#ifndef MATH_RAYH
#define MATH_RAYH

#include "vec3.h"
#include "point3.h"

namespace film { namespace math {

class ray {
public:
  point3 origin;
  vec3 direction;

  ray();
  ray(const point3& origin, const vec3& direction);
  ray(const ray& _ray);
  ~ray();
  ray& operator=(const ray& rhs);
  point3 point_at_parameter(float t) const;
};

} }

#endif
