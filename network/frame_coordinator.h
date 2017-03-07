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

  frame_t(size_t filmWidth, size_t filmHeight)
      : hasSentAllJobs(false),
        jobsTotal(0),
        jobsReceived(0),
        filmPtr(new Film(filmWidth, filmHeight)) {}
};

class FrameCoordinator {
 public:
  FrameCoordinator(size_t filmWidth, size_t filmHeight);
  ~FrameCoordinator();
  void filmJobSent(const quint16 frameId);
  void filmJobReceived(const film_job_t job, std::vector<rgb> pixels);
  void hasSentAllJobs(const quint16 frameId);
  bool isFrameDone(const quint16 frameId);
  Film* getFilm(const quint16 frameId);

 private:
  size_t filmWidth, filmHeight;
  QMap<quint16, frame_t> frames;
  QMutex mutex;

  frame_t& findOrInitialize(const quint16 frameId);
};
}
#endif
