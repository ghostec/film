#include "renderer.h"
#include "math/rgb.h"
#include "math/ray.h"

namespace film { namespace renderer {

Renderer::Renderer() : film(nullptr) {}
Renderer::~Renderer() {}

bool hit_sphere(const math::point3& center, float radius, const math::ray& ray) {
  math::vec3 oc = ray.origin - center;
  float a = ray.direction * ray.direction;
  float b = 2.0 * (oc * ray.direction);
  float c = (oc * oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}

math::rgb color(const math::ray& ray) {
  if (hit_sphere(math::point3(0,0,-1), 0.5, ray))
    return math::rgb(1, 0, 0);
  math::vec3 unit_direction = ray.direction.hat();
  float t = 0.5 * (unit_direction.y + 1.0);
  return (1.0 - t) * math::rgb(1.0) + t * math::rgb(0.5, 0.7, 1.0);
}

void Renderer::render(size_t first_row, size_t last_row, size_t film_width, size_t film_height) {
  set_film(film_width, last_row - first_row + 1);

  math::vec3 lower_left_corner(-2.0, -1.0, -1.0);
  math::vec3 horizontal(4.0, 0.0, 0.0);
  math::vec3 vertical(0.0, 2.0, 0.0);
  math::point3 origin(0.0);

  for(int i = 0; i < film_width; i++) {
    for(int j = 0; j < (last_row - first_row + 1); j++) {
      float u = float(i) / float(film_width);
      float v = float(j + first_row) / float(film_height);
      math::ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
      (*film)[j * film_width + i] = color(ray);
    }
  }
}

void Renderer::set_film(size_t width, size_t height) {
  if(film) delete film;
  film = new Film(width, height);
}

Film* Renderer::get_film() {
  return film;
}

} }
