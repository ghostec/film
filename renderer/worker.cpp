#include <functional>
#include <cstring>
#include <regex>
#include <sstream>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "worker.h"
#include "math/rgb.h"
#include "network/constants.h"
#include "film-network/write.h"
#include "film-network/server.h"

namespace film { namespace renderer {

Worker* Worker::create(const char* ip, int port) {
  auto worker = new Worker(ip, port);
  worker->register_handlers();
  return worker;
}

Worker::Worker(const char* ip, int port) {
  network_client = new network::Client();

  network_client->set_inner_connection_cb([](uv_stream_t* handle) {
    film::network::write({
      .handle = handle,
      .data = film::network::REGISTER_WORKER_MESSAGE,
      .length = strlen(film::network::REGISTER_WORKER_MESSAGE) + 1
    });
  });

  network_client->start(ip, port);
}

void Worker::register_handlers() {
  network_client->register_observer(
    std::bind(&Worker::handle_render_job_message, this, std::placeholders::_1)
  );
}

void Worker::handle_render_job_message(network::Message message) {
  std::smatch matches;
  std::string msg(message.data);

  if (!std::regex_search(msg, matches, network::REGEX_RENDER_JOB)) return;

  int first_row, last_row;
  size_t film_width, film_height;
  std::stringstream(matches[1]) >> first_row;
  std::stringstream(matches[2]) >> last_row;
  std::stringstream(matches[3]) >> film_width;
  std::stringstream(matches[4]) >> film_height;

  if (first_row == -1 || last_row == -1) return;

  work(message.handle, first_row, last_row, film_width, film_height);
}


void Worker::work(uv_stream_t* handle, size_t first_row, size_t last_row, size_t film_width, size_t film_height) {
  std::thread t(&Renderer::render, &renderer, first_row, last_row, film_width, film_height);
  t.join();
  
  const auto& pixels = renderer.get_film()->get_pixels();
  const char* bytes = reinterpret_cast<const char*>(&pixels[0]);
  auto size_of_bytes = sizeof(math::rgb) * pixels.size();

  char buffer[100];
  sprintf(buffer, "%s %zu %zu %zu", network::RENDER_JOB_RESULT_MESSAGE, first_row, last_row, film_width);

  auto v_bytes = new char[strlen(buffer) + 1 + size_of_bytes];
  std::copy(buffer, buffer + strlen(buffer) + 1, v_bytes);
  std::copy(bytes, bytes + size_of_bytes, v_bytes + strlen(buffer) + 1);

  network::write({
    .handle = handle, .data = v_bytes, .length = size_of_bytes + strlen(buffer) + 1
  });

  //delete v_bytes;
}

network::Client* Worker::get_network_client() {
  return network_client;
}


} }
