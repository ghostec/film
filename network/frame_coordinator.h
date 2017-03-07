#ifndef NETWORK_FRAME_COORDINATORH
#define NETWORK_FRAME_COORDINATORH

#include <QMap>

#include "film_job_t.h"
#include "renderer/film.h"

namespace film {
struct frame_t {
  bool hasSentAllJobs;
  quint16 jobsReceived, jobsTotal;
  Film* filmPtr;

  frame_t()
      : hasSentAllJobs(false),
        jobsTotal(0),
        jobsReceived(0),
        filmPtr(nullptr) {}
};

class FrameCoordinator {
 public:
  FrameCoordinator();
  ~FrameCoordinator();
  void filmJobSent(quint16 frameId);
  void filmJobReceived(film_job_t job, std::vector<rgb> pixels);
  void hasSentAllJobs(quint16 frameId);
  bool frameDone(quint16 frameId);
  Film* getFilm(quint16 frameId);

 private:
  QMap<quint16, frame_t> frames;
  QMutex mutex;
};
}
#endif
