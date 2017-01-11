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
  hitable::sphere* sphere1 = new hitable::sphere();
  hitable::sphere* sphere2 = new hitable::sphere({-40, 30, 0}, 85);
  sphere1->SetColor({1,0,0});
  sphere2->SetColor({1,1,0});

  hitable_compose->add(sphere1);
  hitable_compose->add(sphere2);
}

}

}
