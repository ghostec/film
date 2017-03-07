#ifndef CAMERA_CAMERAH
#define CAMERA_CAMERAH

#include "math/point3.h"
#include "math/ray.h"
#include "math/vec3.h"

namespace film {
class Camera {
 public:
  point3 origin, lower_left_corner;
  vec3 horizontal, vertical;

  Camera(point3 look_from, point3 look_at, vec3 up, float vfov, float aspect);
  ray getRay(float u, float v);
};
}

#endif
