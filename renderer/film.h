#ifndef RENDERER_FILMH
#define RENDERER_FILMH

#include <vector>
#include "math/rgb.h"

namespace film { namespace renderer {

class Film {
public:
  Film(size_t width, size_t height);
  ~Film();
  math::rgb operator[](size_t i);
  size_t get_width();
  size_t get_height();
  std::vector<math::rgb>& get_pixels();
private:
  size_t width, height;
  std::vector<math::rgb> pixels;
};

} }

#endif
