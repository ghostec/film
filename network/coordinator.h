#ifndef NETWORK_COORDINATORH
#define NETWORK_COORDINATORH

#include "film_job_coordinator.h"

namespace film {
class Coordinator {
 public:
  Coordinator(size_t filmWidth, size_t filmHeight);
  ~Coordinator();
  FilmJob nextJob();

 private:
  size_t filmWidth, filmHeight;
  FilmJobCoordinator filmJobCoordinator;
};
}

#endif
