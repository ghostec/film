#ifndef NETWORK_FRAME_COORDINATORH
#define NETWORK_FRAME_COORDINATORH

#include <QMap>
#include "renderer/film.h"

namespace film {
struct frame_t {
  bool hasSentAllJobs;
  quint16 jobsReceived, jobsTotal;
  Film* film;

  frame_t()
      : hasSentAllJobs(false), jobsTotal(0), jobsReceived(0), film(nullptr) {}
};

class FrameCoordinator {
 public:
  FrameCoordinator();
  ~FrameCoordinator();
  void jobSent(quint16 frameId);
  void jobReceived(quint16 frameId);
  void hasSentAllJobs(quint16 frameId);
  bool frameDone(quint16 frameId);
  Film* getFilm(quint16 frameId);

 private:
  QMap<quint16, frame_t> frames;
  QMutex mutex;
};
}
#endif
