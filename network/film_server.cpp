#include <algorithm>
#include <regex>
#include <sstream>
#include <iostream>
#include <Magick++.h>
#include <iterator>
#include <cstdio>
#include "film_server.h"
#include "constants.h"
#include "film-network/write.h"

namespace film { namespace network {

FilmServer::FilmServer() : client(nullptr), Server() {
  auto film = new renderer::Film(800, 600);
  coordinator.set_film(film);
  register_observer(std::bind(&FilmServer::handle_worker_message, this, std::placeholders::_1));
  register_observer(std::bind(&FilmServer::handle_client_message, this, std::placeholders::_1));
  register_observer(std::bind(&FilmServer::handle_render_job_result_message, this, std::placeholders::_1));
}

FilmServer::~FilmServer() {}

void FilmServer::handle_client_message(Message message) {
  if(strcmp(message.data, REGISTER_CLIENT_MESSAGE) != 0) return;
  
  client = message.handle;

  send_jpeg();
}


void FilmServer::handle_worker_message(Message message) {
  if(strcmp(message.data, REGISTER_WORKER_MESSAGE) != 0) return;
  
  send_job(message.handle);
}

void FilmServer::handle_render_job_result_message(Message message) {
  std::smatch matches;
  std::string msg(message.data);

  if(!std::regex_search(msg, matches, REGEX_RENDER_JOB_RESULT)) return;

  size_t first_row, last_row;
  size_t film_width;
  std::stringstream(matches[1]) >> first_row;
  std::stringstream(matches[2]) >> last_row;
  std::stringstream(matches[3]) >> film_width;

  math::rgb* rgbs = const_cast<math::rgb*>(
    reinterpret_cast<const math::rgb*>(message.data + msg.size() + 1)
  );

  auto& pixels = coordinator.get_film()->get_pixels();
  std::copy(rgbs, rgbs + (last_row - first_row + 1) * film_width, &pixels[first_row * film_width]);

  send_job(message.handle);
  send_jpeg();
}

void FilmServer::send_jpeg() {
  if (!client) return;
  
  const auto pixels = coordinator.get_film()->get_pixels();
  const auto film = coordinator.get_film();

  Magick::Image im(film->get_width(), film->get_height(), "RGB",
    Magick::StorageType::FloatPixel, (void*) &pixels[0]);
  
  Magick::Blob jpeg;

  im.magick("JPEG");
  im.write(&jpeg);

  auto buf = new char[jpeg.length()];
  std::memcpy(buf, jpeg.data(), jpeg.length());

  network::write({
    .handle = client,
    .data = buf,
    .length = jpeg.length()
  });
}

void FilmServer::send_job(uv_stream_t* handle) {
  char buffer[100];

  auto film = coordinator.get_film();
  auto job = coordinator.next_job();
  sprintf(buffer, "%s %d %d %zu", RENDER_JOB_MESSAGE, job.first_row, job.last_row, film->get_width());
  printf("%s\n", buffer);

  network::write({
    .handle = handle,
    .data = buffer,
    .length = strlen(buffer) + 1
  });
}

} }
