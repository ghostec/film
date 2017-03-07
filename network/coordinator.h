#ifndef NETWORK_COORDINATORH
#define NETWORK_COORDINATORH

#include <QObject>
#include <vector>

#include "film_job_coordinator.h"
#include "frame_coordinator.h"

namespace film {
class Coordinator : public QObject {
  Q_OBJECT
 public:
  Coordinator(size_t filmWidth, size_t filmHeight);
  ~Coordinator();
  film_job_t nextJob();
  void filmJobReceived(film_job_t job, std::vector<rgb> pixels);

 signals:
  void frameDone(Film* filmPtr);

 private:
  size_t filmWidth, filmHeight;
  FilmJobCoordinator filmJobCoordinator;
  FrameCoordinator frameCoordinator;
};
}

#endif
