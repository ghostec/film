#ifndef FILM_JOB_COORDINATORH
#define FILM_JOB_COORDINATORH

#include <QMutex>

struct FilmJob {
  quint16 frameId, width, height, firstRow, lastRow;
};

class FilmJobCoordinator {
 public:
  FilmJobCoordinator(size_t filmWidth, size_t filmHeight);
  FilmJobCoordinator(const FilmJobCoordinator& c);
  ~FilmJobCoordinator();
  FilmJob nextJob();

 private:
  size_t filmWidth, filmHeight;
  quint16 frameId, rowStep, currentRow;
  QMutex mutex;

  FilmJob _nextJob(quint16 lastRow);
};

#endif
