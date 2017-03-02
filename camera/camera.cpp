#include <cmath>
#include "camera.h"

namespace film { namespace camera {

Camera::Camera(math::point3 look_from, math::point3 look_at, math::vec3 up,
  float vfov, float aspect) {
  math::vec3 u, v, w;
  float theta = vfov * M_PI / 180;
  float half_height = tan(theta/2);
  float half_width = aspect * half_height;
  origin = look_from;
  w = (look_from - look_at).hat();
  u = (up ^ w).hat();
  v = w ^ u;
  //lower_left_corner = math::vec3(-half_width, -half_height, -1);
  lower_left_corner = origin - half_width * u - half_height * v - w;
  horizontal = 2 * half_width * u;
  vertical = 2 * half_height * v;
}

math::ray Camera::get_ray(float s, float t) {
  return math::ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
}

} }
