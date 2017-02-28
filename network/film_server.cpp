#include "film_server.h"
#include "constants.h"
#include "film-network/write.h"
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
  }
  lock.unlock();

  if (is_client(message.handle)) {
    return;
  } else if (is_worker(message.handle)) {
    handle_worker_message(message);
  }
}

void FilmServer::handle_worker_message(Message message) {
  if(strcmp(message.data, REGISTER_WORKER_MESSAGE) == 0) {
    network::write({
      .handle = message.handle,
      .data = "SET_FILM 800 600",
      .length = 17
    });
  }
}

} }
