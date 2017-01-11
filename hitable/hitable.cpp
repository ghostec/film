#include "hitable.h"

namespace film {

namespace hitable {

hitable::hitable() : color(math::rgb()) {}

void hitable::SetColor(const math::rgb _color) {
  color = _color;
}

}

}
