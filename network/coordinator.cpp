#include "coordinator.h"
#include <QtDebug>

namespace film {
Coordinator::Coordinator(size_t filmWidth, size_t filmHeight)
    : waiting(false),
      filmWidth(filmWidth),
      filmHeight(filmHeight),
      filmJobCoordinator(filmWidth, filmHeight),
      frameCoordinator(filmWidth, filmHeight) {}

Coordinator::~Coordinator() {}

film_job_t Coordinator::nextFilmJob() {
  std::unique_lock<std::mutex> lock(mutex);
  while (waiting) cv.wait(lock);

  auto job = filmJobCoordinator.nextFilmJob();
  frameCoordinator.filmJobSent(job.frameId);
  if (job.lastRow == filmHeight - 1) {  // last job for that frame
    frameCoordinator.hasSentAllJobs(job.frameId);
    // lock Coordinator from calling nextFilmJob until Server updates Scene
    waiting = true;
    emit allFilmJobsSentForCurrentFrame();
  }
  return job;
}

void Coordinator::proceedWithFilmJobs() {
  waiting = false;
  cv.notify_all();
}

void Coordinator::filmJobReceived(film_job_t job, std::vector<rgb> pixels) {
  frameCoordinator.filmJobReceived(job, pixels);
  if (frameCoordinator.isFrameDone(job.frameId)) {
    emit frameDone(frameCoordinator.getFilm(job.frameId));
  }
}
}

#include "moc_coordinator.cpp"
