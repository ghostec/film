#include "film_job_coordinator.h"

FilmJobCoordinator::FilmJobCoordinator() : currentRow(0), rowStep(10) {}

FilmJob FilmJobCoordinator::nextJob() {
  mutex.lock();

  mutex.unlock();
}

#include "moc_film_job_coordinator.cpp"
