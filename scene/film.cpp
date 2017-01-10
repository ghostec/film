#include <cmath>
#include "film.h"

namespace film {

namespace scene {

film::film(size_t _hres, size_t _vres, float _s) : hres(_hres), vres(_vres), s(_s) {
  pixels.resize(hres * vres);
}

film::~film() {}

math::rgb& film::operator[](size_t i) {
  return pixels[i];
}

size_t film::GetHres() const {
  return hres;
}

size_t film::GetVres() const {
  return vres;
}

size_t film::GetS() const {
  return s;
}

void film::SavePPM() const {
  FILE* f = fopen("image.ppm", "w");
  fprintf(f, "P3\n%zu %zu\n%d\n", hres, vres, 255);
  for(auto i = 0; i < vres; i++) {
    for(auto j = 0; j < hres; j++) {
      const auto p = hres * (vres - i - 1) + j;
      const auto rgb = pixels[p].ToIntArray();
      fprintf(f, "%d %d %d ", rgb[0], rgb[1], rgb[2]);
    }
  }
}

}

}
