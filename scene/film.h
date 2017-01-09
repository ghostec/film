#ifndef FILMH
#define FILMH

#include <vector>
#include "math/rgb.h"

namespace film {

namespace scene {

class film {
public:
  film(size_t _hres, size_t _vres, float _s = 1.0);
  ~film();
  math::rgb& operator[](size_t i);
  size_t GetHres() const;
  size_t GetVres() const;
  size_t GetS() const;
private:
  size_t hres, vres;
  float s;
  float gamma, invgamma;
  std::vector<math::rgb> pixels;
};

}

}

#endif
