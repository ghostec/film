#include <mutex>
#include <utility>

#include "film.h"

namespace film {
Film::Film(size_t width, size_t height)
    : width(width), height(height), pixels(std::vector<rgb>(width * height)) {}

Film::~Film() {}

void Film::setBlock(const std::vector<rgb> pixels, size_t toIndex) {
  std::copy(&pixels[0], &pixels[0] + pixels.size(), &this->pixels[toIndex]);
}

std::vector<rgb> Film::getPixels() const { return pixels; }
}
