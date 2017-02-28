#include "film.h"

namespace film { namespace renderer {

Film::Film(size_t width, size_t height) :
  pixels(std::vector<math::rgb>(width * height, math::rgb())),
  width(width), height(height) {}

math::rgb Film::operator[](size_t i) {
  return pixels[i];
}

size_t Film::get_width() {
  return width;
}

size_t Film::get_height() {
  return height;
}

} }
