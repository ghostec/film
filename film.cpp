#include <iostream>
#include <functional>
#include <Magick++.h>
#include <string>
#include "film-network/write.h"
#include "film.h"

namespace film {

Film::Film() {}
Film::~Film() {}

void Film::set_server(network::Server* server) {
  // unregister if server

  this->server = server;
  server->register_observer(std::bind(&Film::handle_message, this, std::placeholders::_1));
}

void Film::handle_message(network::Message message) {
  size_t height = 100, width = 100;
  auto pixels = std::vector<float>(width * height * 3, 0.5);
  Magick::Image im(width, height, "RGB", Magick::StorageType::FloatPixel, (void*) &pixels[0]);
  //Magick::Image im;
  //im.read("test.png");
  im.magick("JPEG");

  Magick::Blob jpeg;
  im.write(&jpeg);

  auto buf = new char[jpeg.length()];
  memcpy(buf, jpeg.data(), jpeg.length());

  network::Message message_to_send = { .handle = message.handle, .data = buf, .length = jpeg.length() };
  network::write(message_to_send);
}

}
