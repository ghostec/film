#ifndef NETWORK_COORDINATORH
#define NETWORK_COORDINATORH

#include "film_job_coordinator.h"
#include "frame_coordinator.h"

namespace film {
class Coordinator {
 public:
  Coordinator(size_t filmWidth, size_t filmHeight);
  ~Coordinator();
  film_job_t nextJob();
  void jobReceived(quint16 frameId);

 private:
  size_t filmWidth, filmHeight;
  FilmJobCoordinator filmJobCoordinator;
  FrameCoordinator frameCoordinator;
};
}

#endif
