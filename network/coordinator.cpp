#include "coordinator.h"
#include <QtDebug>

namespace film {
Coordinator::Coordinator(size_t filmWidth, size_t filmHeight)
    : filmWidth(filmWidth),
      filmHeight(filmHeight),
      filmJobCoordinator(filmWidth, filmHeight),
      frameCoordinator(filmWidth, filmHeight) {}

Coordinator::~Coordinator() {}

film_job_t Coordinator::nextJob() {
  // Get Job and create new frame if necessary
  // Another function to update frame status on FrameCoordinator

  auto job = filmJobCoordinator.nextJob();
  if (job.lastRow == filmHeight - 1) {  // last job for that frame
    frameCoordinator.hasSentAllJobs(job.frameId);
  }
  frameCoordinator.filmJobSent(job.frameId);
  return job;
}

void Coordinator::filmJobReceived(film_job_t job, std::vector<rgb> pixels) {
  frameCoordinator.filmJobReceived(job, pixels);
  if (frameCoordinator.isFrameDone(job.frameId)) {
    emit frameDone(frameCoordinator.getFilm(job.frameId));
  }
}
}

#include "moc_coordinator.cpp"
