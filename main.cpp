#include <Magick++.h>
#include <vector>
#include <array>
#include <stdint.h>
#include "film.h"
#include "server/server.h"

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);

  film::Film film;
  film::server::Server* server = new film::server::Server();

  film.set_server(server);

  server->start();
  return 0;
}
