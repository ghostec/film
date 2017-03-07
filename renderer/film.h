#ifndef RENDERER_FILMH
#define RENDERER_FILMH

#include <vector>

#include "math/rgb.h"

namespace film {
class Film {
 public:
  Film(size_t width, size_t height);
  ~Film();
  void setBlock(const std::vector<rgb> pixels, size_t toIndex);
  std::vector<rgb> getPixels() const;
  size_t getWidth() const;
  size_t getHeight() const;
  rgb& operator[](size_t i);

 private:
  std::vector<rgb> pixels;
  size_t width, height;
};
}

#endif
