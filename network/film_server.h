#ifndef NETWORK_FILMSERVERH
#define NETWORK_FILMSERVERH

#include <unordered_map>
#include <string>
#include <mutex>
#include <uv.h>
#include "film-network/message.h"
#include "film-network/server.h"
#include "coordinator.h"

namespace film { namespace network {

class FilmServer : public Server {
public:
  FilmServer();
  ~FilmServer();
private:
  uv_stream_t* client;
  Coordinator coordinator;

  void handle_worker_message(Message message);
  void handle_client_message(Message message);
  void handle_render_job_result_message(Message message);
  void send_jpeg();
  void send_job(uv_stream_t* handle);
};

} }

#endif
