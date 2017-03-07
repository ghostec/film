#include <cmath>

#include "camera.h"

namespace film {
Camera::Camera(point3 look_from, point3 look_at, vec3 up, float vfov,
               float aspect) {
  vec3 u, v, w;
  float theta = vfov * M_PI / 180;
  float half_height = tan(theta / 2);
  float half_width = aspect * half_height;
  origin = look_from;
  w = (look_from - look_at).hat();
  u = (up ^ w).hat();
  v = w ^ u;
  lower_left_corner = origin - half_width * u - half_height * v - w;
  horizontal = 2 * half_width * u;
  vertical = 2 * half_height * v;
}

ray Camera::getRay(float s, float t) {
  return ray(origin,
             lower_left_corner + s * horizontal + t * vertical - origin);
}
}
