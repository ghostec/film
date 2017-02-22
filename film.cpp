#include <iostream>
#include <functional>
#include "film.h"

namespace film {

Film::Film() {}
Film::~Film() {}

void Film::set_server(server::Server* server) {
  // unregister if server

  this->server = server;
  server->register_observer(std::bind(&Film::handle_message, this, std::placeholders::_1));
}

void Film::handle_message(server::Message message) {
  std::cout << message.data + '\n';
}

}
