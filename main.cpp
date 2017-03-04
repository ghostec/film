#include <iostream>
#include <functional>
#include <mutex>
#include <uv.h>
#include <Magick++.h>
#include "film.h"
#include "film-network/write.h"
#include "network/film_server.h"
#include "network/constants.h"
#include "renderer/worker.h"

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);

  auto server = new film::network::FilmServer();
  server->start("0.0.0.0", 3001);

  auto worker = film::renderer::Worker::create("0.0.0.0", 3001);
  worker->loop();

  std::mutex m;
  m.lock();
  m.lock();
  return 0;
}
