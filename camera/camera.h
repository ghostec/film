#ifndef CAMERA_CAMERAH
#define CAMERA_CAMERAH

#include "hitable/hitable.h"
#include "math/point3.h"
#include "math/ray.h"
#include "math/vec3.h"
#include "renderer/film.h"

namespace film {
class Camera {
 public:
  point3 origin, lower_left_corner;
  vec3 horizontal, vertical;

  Camera(point3 origin, point3 lowerLeftCorner, vec3 horizontal, vec3 vertical);
  Camera(point3 look_from, point3 look_at, vec3 up, float vfov, float aspect);
  ray getRay(float u, float v);
  void render(Film* filmPtr, Hitable* worldPtr, size_t firstRow, size_t lastRow,
              size_t width, size_t height);
};
}

#endif
