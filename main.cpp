#include "film.h"
#include "server/server.h"

int main() {
  film::Film film;
  film::server::Server* server = new film::server::Server();

  film.set_server(server);

  server->start();
  return 0;
}
