#ifndef NETWORK_COORDINATORH
#define NETWORK_COORDINATORH

#include <vector>

#include "film_job_coordinator.h"
#include "frame_coordinator.h"

namespace film {
class Coordinator {
 public:
  Coordinator(size_t filmWidth, size_t filmHeight);
  ~Coordinator();
  film_job_t nextJob();
  void filmJobReceived(film_job_t job, std::vector<rgb> pixels);

 private:
  size_t filmWidth, filmHeight;
  FilmJobCoordinator filmJobCoordinator;
  FrameCoordinator frameCoordinator;
};
}

#endif
