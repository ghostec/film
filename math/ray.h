#ifndef RAYH
#define RAYH

#include "vec3.h"
#include "point3.h"

namespace film {

namespace math {

class ray {
public:
  point3 origin;
  vec3 direction;

  ray();
  ray(const point3& _origin, const vec3& direction);
  ray(const ray& _ray);
  ~ray();
  ray& operator=(const ray& rhs);
};

}

}

#endif
