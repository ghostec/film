#ifndef RANDOMH
#define RANDOMH

#include <cstdlib>

#include "constants.h"

namespace film {

namespace math {

inline float rand_float() {
  return static_cast<float>(rand() * INVRAND_MAX);
}

}

}

#endif
