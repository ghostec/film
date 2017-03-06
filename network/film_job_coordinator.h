#ifndef FILM_JOB_COORDINATORH
#define FILM_JOB_COORDINATORH

#include <QMutex>

struct FilmJob {
  quint16 frameId, width, height, firstRow, lastRow;
};

class FilmJobCoordinator {
 public:
  FilmJobCoordinator();
  FilmJob nextJob();

 private:
  quint16 rowStep;
  quint16 currentRow;
  QMutex mutex;
}

#endif
