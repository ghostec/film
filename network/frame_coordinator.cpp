#include "frame_coordinator.h"

namespace film {
FrameCoordinator::FrameCoordinator(size_t filmWidth, size_t filmHeight)
    : filmWidth(filmWidth), filmHeight(filmHeight) {}
FrameCoordinator::~FrameCoordinator() {}

frame_t& FrameCoordinator::findOrInitialize(const quint16 frameId) {
  if (frames.contains(frameId)) return frames.find(frameId).value();
  return frames.insert(frameId, frame_t(filmWidth, filmHeight)).value();
}

void FrameCoordinator::filmJobSent(const quint16 frameId) {
  mutex.lock();
  auto& frame = findOrInitialize(frameId);
  frame.jobsTotal += 1;
  mutex.unlock();
}

void FrameCoordinator::filmJobReceived(const film_job_t job,
                                       std::vector<rgb> pixels) {
  mutex.lock();
  auto& frame = findOrInitialize(job.frameId);
  frame.jobsReceived += 1;
  frame.filmPtr->setBlock(std::move(pixels), job.width * job.firstRow);
  mutex.unlock();
}

void FrameCoordinator::hasSentAllJobs(const quint16 frameId) {
  mutex.lock();
  findOrInitialize(frameId).hasSentAllJobs = true;
  mutex.unlock();
}

bool FrameCoordinator::isFrameDone(const quint16 frameId) {
  mutex.lock();
  auto& frame = findOrInitialize(frameId);
  auto ret = ((frame.hasSentAllJobs && (frame.jobsTotal == frame.jobsReceived))
                  ? true
                  : false);
  mutex.unlock();
  return ret;
}

Film* FrameCoordinator::getFilm(const quint16 frameId) {
  return findOrInitialize(frameId).filmPtr;
}
}
