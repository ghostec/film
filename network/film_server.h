#ifndef NETWORK_FILMSERVERH
#define NETWORK_FILMSERVERH

#include <unordered_map>
#include <string>
#include <mutex>
#include <uv.h>
#include "film-network/message.h"
#include "film-network/server.h"

namespace film { namespace network {

class FilmServer : public Server {
public:
  FilmServer();
  ~FilmServer();
private:
  std::mutex m_handle_message;
  std::unordered_map<uv_stream_t*, std::string> handles;

  void handle_message(Message message);
  void handle_worker_message(Message message);
  void handle_client_message(Message message);
  bool is_client(uv_stream_t* handle);
  bool is_worker(uv_stream_t* handle);
};

} }

#endif
