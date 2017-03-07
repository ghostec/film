#ifndef RENDERER_FILMH
#define RENDERER_FILMH

#include <shared_mutex>
#include <vector>

#include "math/rgb.h"

namespace film {
class Film {
 public:
  Film(size_t width, size_t height);
  ~Film();
  void setBlock(rgb* pixels, size_t blockSize, size_t toIndex);
  std::vector<rgb> getPixels();

 private:
  std::shared_timed_mutex mutex;
  std::vector<rgb> pixels;
  size_t width, height;
};
}

#endif
