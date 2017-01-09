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

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

void film::SavePPM() const {
  FILE* f = fopen("image.ppm", "w");
  fprintf(f, "P3\n%zu %zu\n%d\n", hres, vres, 255);
  for(auto i = 0; i < vres; i++) {
    for(auto j = 0; j < hres; j++) {
      const auto p = hres * (vres - i - 1) + j;
      fprintf(f, "%d %d %d ", toInt(pixels[p].r), toInt(pixels[p].g), toInt(pixels[p].b));
    }
  }
}

}

}
