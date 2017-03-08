#include <cmath>
#include <limits>

#include "camera.h"
#include "math/rgb.h"

namespace film {
Camera::Camera(point3 origin, point3 lowerLeftCorner, vec3 horizontal,
               vec3 vertical)
    : origin(origin),
      lower_left_corner(lowerLeftCorner),
      horizontal(horizontal),
      vertical(vertical) {}

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

rgb color(const ray& ray, const Hitable* worldPtr) {
  auto hit_record = worldPtr->hit(ray, 0, std::numeric_limits<float>::max());
  if (hit_record.hit) return rgb(1, 0, 0);
  vec3 unit_direction = ray.direction.hat();
  float t = 0.5 * (unit_direction.y + 1.0);
  return (1.0 - t) * rgb(1.0) + t * rgb(0.5, 0.7, 1.0);
}

void Camera::render(Film* filmPtr, Hitable* worldPtr, size_t firstRow,
                    size_t lastRow, size_t width, size_t height) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < (lastRow - firstRow + 1); j++) {
      float u = float(i) / float(width);
      float v = float(j + firstRow) / float(height);
      auto ray = getRay(u, v);
      (*filmPtr)[j * width + i] = color(ray, worldPtr);
    }
  }
}
}
