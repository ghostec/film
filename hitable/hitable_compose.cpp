#include <cmath>
#include "hitable_compose.h"

namespace film {

namespace hitable {

hitable_compose::hitable_compose() {}

bool hitable_compose::hit(const math::ray& ray, double& t_min, hit_record& rec) const {
  double t = t_min;
  hit_record temp_rec;
  bool _hit = false;
  
  for(const auto& h : hitables) {
    if(h->hit(ray, t_min, rec) && t_min < t) {
      t = t_min;
      temp_rec = rec;
      _hit = true;
    }
  }

  t_min = t;
  rec = temp_rec;
  return _hit;
}

void hitable_compose::add(hitable* _hitable) {
  hitables.push_back(_hitable);
}

}

}


