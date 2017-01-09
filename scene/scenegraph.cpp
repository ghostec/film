#include "scenegraph.h"
#include "hitable/sphere.h"

namespace film {

namespace scene {

scenegraph::scenegraph() {}

scenegraph::~scenegraph() {}

std::vector<hitable::hitable> scenegraph::GetObjects() const {
  return objects;
}

void scenegraph::build() {
  hitable::sphere sphere;

  objects.push_back(sphere);
}

}

}
