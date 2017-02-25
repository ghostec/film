#include <iostream>
#include <functional>
#include <Magick++.h>
#include <string>
#include "server/write.h"
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
    rgb() { r = 255; }
  } __attribute__((__packed__));

  auto height = 100, width = 100;
  auto pixels = std::vector<rgb>(width * height, rgb());
  std::cout << pixels[0].r << std::endl;
  Magick::Image im(Magick::Geometry(100, 100), Magick::ColorRGB(1.0, 0.0, 0.0));
  Magick::Blob jpeg;
  im.magick("JPEG");
  im.write(&jpeg);

  auto buf = new char[jpeg.length()];
  memcpy(buf, jpeg.data(), jpeg.length());

  server::Message message_to_send = { .handle = message.handle, .data = buf, .length = jpeg.length() };
  server::write(message_to_send);
}

}
