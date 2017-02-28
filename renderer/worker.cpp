#include <functional>
#include <cstring>
#include <iostream>
#include <regex>
#include <sstream>
#include "worker.h"
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
    std::bind(&Worker::handle_set_film_message, this, std::placeholders::_1)
  );
}

void Worker::handle_set_film_message(network::Message message) {
  std::smatch matches;
  std::string msg(message.data);
  
  if(std::regex_search(msg, matches, network::REGEX_SET_FILM)) {
    size_t width, height;
    std::stringstream(matches[1]) >> width;
    std::stringstream(matches[2]) >> height;
    auto film = new renderer::Film(width, height);
    renderer.set_film(film);
  }
}

void Worker::work(Job job) {
  return;
}

network::Client* Worker::get_network_client() {
  return network_client;
}


} }
