#include <Magick++.h>
#include <vector>
#include <array>
#include <stdint.h>
#include "film.h"
#include "film-network/server.h"

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);

  film::Film film;
  film::network::Server* server = new film::network::Server();

  film.set_server(server);

  server->start();
  return 0;
}
