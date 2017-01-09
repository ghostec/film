#include "film.h"

namespace film {

namespace scene {

film::film(size_t _hres, size_t _vres, float _s) : hres(_hres), vres(_vres), s(_s) {
  pixels.resize(hres * vres);
}

film::~film() {}

math::rgb film::operator[](size_t i) const {
  return pixels[i];
}

}

}
