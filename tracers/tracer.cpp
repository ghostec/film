#include "tracer.h"

namespace film {

namespace tracers {

tracer::tracer() : scenegraph(nullptr) {}

tracer::tracer(scene::scenegraph* _scenegraph) : scenegraph(_scenegraph) {}

tracer::~tracer() {
  scenegraph = nullptr;
}

math::rgb tracer::TraceRay(const math::ray ray, const hitable::hitable* scene) const {
  return {0.0};
}

}

}
