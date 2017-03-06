#include "coordinator.h"

namespace film {
Coordinator::Coordinator(size_t filmWidth, size_t filmHeight)
    : filmWidth(filmWidth),
      filmHeight(filmHeight),
      filmJobCoordinator(FilmJobCoordinator(filmWidth, filmHeight)) {}

Coordinator::~Coordinator() {}

FilmJob Coordinator::nextJob() {
  // Get Job and create new frame if necessary
  // Another function to update frame status on FrameCoordinator
  return filmJobCoordinator.nextJob();
}
}
