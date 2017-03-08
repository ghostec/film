#ifndef NETWORK_COORDINATORH
#define NETWORK_COORDINATORH

#include <QObject>
#include <condition_variable>
#include <mutex>
#include <vector>

#include "film_job_coordinator.h"
#include "frame_coordinator.h"

namespace film {
class Coordinator : public QObject {
  Q_OBJECT
 public:
  Coordinator(size_t filmWidth, size_t filmHeight);
  ~Coordinator();
  film_job_t nextFilmJob();
  void filmJobReceived(film_job_t job, std::vector<rgb> pixels);
  void proceedWithFilmJobs();

 signals:
  void frameDone(Film* filmPtr);
  void allFilmJobsSentForCurrentFrame();

 private:
  size_t filmWidth, filmHeight;
  std::condition_variable cv;
  std::mutex mutex;
  bool waiting;
  FilmJobCoordinator filmJobCoordinator;
  FrameCoordinator frameCoordinator;
};
}

#endif
