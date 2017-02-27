#include <iostream>
#include <functional>
#include <mutex>
#include <uv.h>
#include "film.h"
#include "film-network/server.h"
#include "renderer/worker.h"

void print(film::network::Message message) {
  std::cout << message.data << std::endl;
}

int main(int argc, char **argv) {
  auto server = new film::network::Server();
  server->start("0.0.0.0", 3001);
  server->register_observer(std::bind(print, std::placeholders::_1));

  auto worker = film::renderer::Worker::create("0.0.0.0", 3001);

  std::mutex m;
  m.lock();
  m.lock();
  return 0;
}
