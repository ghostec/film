#include "coordinator.h"

namespace film { namespace network {

Coordinator::Coordinator() : current_row(0), job_size(10) {}
Coordinator::~Coordinator() {}

void Coordinator::set_film(renderer::Film* film) {
  this->film = film;
}

renderer::Film* Coordinator::get_film() {
  return film;
}

RenderJob Coordinator::next_job() {
  const auto rows = film->get_height();
  std::lock_guard<std::mutex> lock(m_current_row);
  if (current_row >= rows) return { -1, -1 };
  if (current_row + job_size >= rows) {
    RenderJob job = { current_row, (int) rows - 1 };
    current_row = rows;
    return job;
  }
  RenderJob job = { current_row, current_row + job_size - 1 };
  current_row += job_size;
  return job;
}

} }
