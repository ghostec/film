#include <iostream>
#include <functional>
#include <Magick++.h>
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
  struct rgb
  {
    uint16_t r,g,b;
  } __attribute__((__packed__));

  auto height = 100, width = 100;
  auto pixels = std::vector<rgb>(width * height, rgb());
  Magick::Image im;
  im.size("100x100");
  im.magick("RGB");
  Magick::Blob blob(&pixels[0], pixels.size() * sizeof(pixels[0]));
  im.read(blob);
  Magick::Blob jpeg;
  im.magick("JPEG");
  im.write(&jpeg);

  //message.data += '\n';
  message.data = jpeg.base64() + '\n';
  server->write(message);
}

}
