#include "film_job_coordinator.h"

FilmJobCoordinator::FilmJobCoordinator(size_t filmWidth, size_t filmHeight)
    : filmWidth(filmWidth),
      filmHeight(filmHeight),
      frameId(0),
      currentRow(0),
      rowStep(10) {}

FilmJobCoordinator::FilmJobCoordinator(const FilmJobCoordinator& c)
    : filmWidth(c.filmWidth), filmHeight(c.filmHeight), rowStep(c.rowStep) {}

FilmJobCoordinator::~FilmJobCoordinator() {}

FilmJob FilmJobCoordinator::_nextJob(quint16 lastRow) {
  return {.frameId = frameId,
          .width = static_cast<quint16>(filmWidth),
          .height = static_cast<quint16>(filmHeight),
          .firstRow = currentRow,
          .lastRow = lastRow};
}

FilmJob FilmJobCoordinator::nextJob() {
  mutex.lock();

  FilmJob job;

  if (currentRow >= filmHeight) {
    currentRow = 0;
    frameId += 1;
    job = _nextJob(currentRow + rowStep);
  } else if (currentRow + rowStep >= filmHeight) {
    job = _nextJob(filmHeight - 1);
  } else {
    job = _nextJob(currentRow + rowStep);
  }

  currentRow += rowStep;

  mutex.unlock();
  return job;
}

#include "moc_film_job_coordinator.cpp"
