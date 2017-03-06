#include <mutex>
#include <utility>

#include "film.h"

namespace film {
Film::Film(size_t width, size_t height)
    : width(width),
      height(height),
      pixels(std::vector<rgb>(rgb, width * height)) {}

Film::~Film() {}

void Film::setBlock(rgb* pixels, size_t blockSize, size_t toIndex) {
  std::shared_lock<std::shared_timed_mutex> lock(mutex);
  std::copy(rgbs, rgbs + blockSize, &pixels[toIndex]);
  lock.unlock();
}

std::vector<rgb> Film::pixels() {
  std::unique_lock<std::shared_timed_mutex> lock(mutex);
  auto copy(pixels);
  lock.unlock();
  return copy;
}
}
