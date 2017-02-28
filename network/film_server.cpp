#include "film_server.h"
#include "constants.h"
#include <iostream>

namespace film { namespace network {

FilmServer::FilmServer() : Server() {
  register_observer(std::bind(&FilmServer::handle_message, this, std::placeholders::_1));
}

FilmServer::~FilmServer() {}

bool FilmServer::is_client(uv_stream_t* handle) {
  return (handles[handle] == CLIENT ? true : false);
}

bool FilmServer::is_worker(uv_stream_t* handle) {
  return (handles[handle] == WORKER ? true : false);
}

void FilmServer::handle_message(Message message) {
  std::unique_lock<std::mutex> lock(m_handle_message);
  if (handles.find(message.handle) == handles.end()) {
    handles[message.handle] = std::string(message.data);
    lock.unlock();
    return;
  }
  lock.unlock();

  std::cout << "MSG: " << message.data << std::endl;
  if (is_client(message.handle)) {
    return;
  } else if (is_worker(message.handle)) {
    std::cout << "WORKER: " << message.data << std::endl;
  }
}

} }
