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
  void handle_message(Message message);
private:
  std::mutex m_handle_message;
  std::unordered_map<uv_stream_t*, std::string> handles;

  bool is_client(uv_stream_t* handle);
  bool is_worker(uv_stream_t* handle);
};

} }

#endif
