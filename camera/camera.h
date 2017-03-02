#ifndef CAMERA_CAMERAH
#define CAMERA_CAMERAH

#include "math/vec3.h"
#include "math/point3.h"
#include "math/ray.h"

namespace film { namespace camera {

class Camera {
public:
  math::point3 origin, lower_left_corner;
  math::vec3 horizontal, vertical;

  Camera(math::point3 look_from, math::point3 look_at, math::vec3 up, float vfov,
    float aspect);
  math::ray get_ray(float u, float v);
};

} }

#endif
