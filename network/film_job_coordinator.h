#ifndef NETWORK_FILM_JOB_COORDINATORH
#define NETWORK_FILM_JOB_COORDINATORH

#include <QMutex>

#include "film_job_t.h"

namespace film {
class FilmJobCoordinator {
 public:
  FilmJobCoordinator(size_t filmWidth, size_t filmHeight);
  FilmJobCoordinator(const FilmJobCoordinator& c);
  ~FilmJobCoordinator();
  film_job_t nextJob();

 private:
  size_t filmWidth, filmHeight;
  quint16 frameId, rowStep, currentRow;
  QMutex mutex;

  film_job_t _nextJob(quint16 lastRow);
};
}

#endif
