#include "scenegraph.h"
#include "hitable/sphere.h"

namespace film {

namespace scene {

scenegraph::scenegraph() : hitable_compose(new hitable::hitable_compose()) {}

scenegraph::~scenegraph() {
  delete hitable_compose;
}

hitable::hitable* scenegraph::GetObjects() const {
  return hitable_compose;
}

void scenegraph::Build() {
  hitable::sphere* sphere = new hitable::sphere();

  hitable_compose->add(sphere);
}

}

}
