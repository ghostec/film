#include "film_job_coordinator.h"

namespace film {
FilmJobCoordinator::FilmJobCoordinator(size_t filmWidth, size_t filmHeight)
    : filmWidth(filmWidth),
      filmHeight(filmHeight),
      frameId(0),
      currentRow(0),
      rowStep(10) {}

FilmJobCoordinator::FilmJobCoordinator(const FilmJobCoordinator& c)
    : filmWidth(c.filmWidth), filmHeight(c.filmHeight), rowStep(c.rowStep) {}

FilmJobCoordinator::~FilmJobCoordinator() {}

film_job_t FilmJobCoordinator::_nextFilmJob(quint16 lastRow) {
  return {.frameId = frameId,
          .width = static_cast<quint16>(filmWidth),
          .height = static_cast<quint16>(filmHeight),
          .firstRow = currentRow,
          .lastRow = lastRow};
}

film_job_t FilmJobCoordinator::nextFilmJob() {
  mutex.lock();

  film_job_t job;

  if (currentRow >= filmHeight) {
    currentRow = 0;
    frameId += 1;
    job = _nextFilmJob(currentRow + rowStep);
  } else if (currentRow + rowStep >= filmHeight) {
    job = _nextFilmJob(filmHeight - 1);
  } else {
    job = _nextFilmJob(currentRow + rowStep);
  }

  currentRow += rowStep;

  mutex.unlock();
  return job;
}
}

#include "moc_film_job_coordinator.cpp"
