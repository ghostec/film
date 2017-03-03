#include <iostream>
#include "coordinator.h"

namespace film { namespace network {

Coordinator::Coordinator() : current_row(0), frame_id(0), job_size(10) {}
Coordinator::~Coordinator() {}

void Coordinator::set_film(renderer::Film* film) {
  this->film = film;
}

renderer::Film* Coordinator::get_film() {
  return film;
}

size_t Coordinator::get_frame_id() {
  return frame_id;
}

RenderJob Coordinator::next_job() {
  const auto rows = film->get_height();
  std::unique_lock<std::mutex> lock(m_current_row);
  if (current_row >= rows) {
    current_row = 0;
    frame_id += 1;
    lock.unlock();
    return next_job();
  };
  if (current_row + job_size >= rows) {
    RenderJob job = {
      .frame_id = frame_id,
      .first_row = current_row,
      .last_row = (int) rows - 1
    };
    current_row = rows;
    lock.unlock();
    return job;
  }
  RenderJob job = {
    .frame_id = frame_id,
    .first_row = current_row,
    .last_row = current_row + job_size - 1
  };
  current_row += job_size;
  lock.unlock();
  return job;
}

} }
