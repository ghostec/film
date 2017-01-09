#include "scenegraph.h"
#include "hitable/sphere.h"

namespace film {

namespace scene {

scenegraph::scenegraph() {}

scenegraph::~scenegraph() {}

std::vector<hitable::hitable*> scenegraph::GetObjects() const {
  return objects;
}

void scenegraph::Build() {
  hitable::sphere* sphere = new hitable::sphere();

  objects.push_back(sphere);
}

}

}
