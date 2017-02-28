#include <functional>
#include <cstring>
#include "worker.h"
#include "network/constants.h"
#include "film-network/write.h"
#include "film-network/server.h"

namespace film { namespace renderer {

Worker* Worker::create(const char* ip, int port) {
  auto worker = new Worker(ip, port);
  auto network_client = worker->get_network_client();
  network_client->register_observer(std::bind(&Worker::handle_message, worker, std::placeholders::_1));
  return worker;
}

Worker::Worker(const char* ip, int port) {
  network_client = new network::Client();

  network_client->set_inner_connection_cb([](uv_stream_t* handle) {
    film::network::write({
      .handle = handle,
      .data = film::network::REGISTER_WORKER_MESSAGE,
      .length = strlen(film::network::REGISTER_WORKER_MESSAGE) + 1
    });
  });

  network_client->start(ip, port);
}

void Worker::work(Job job) {
  return;
}

void Worker::handle_message(network::Message message) {
  return;
}

network::Client* Worker::get_network_client() {
  return network_client;
}


} }
