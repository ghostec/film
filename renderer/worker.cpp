#include <functional>
#include <cstring>
#include "worker.h"
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
  network_client->start(ip, port);
}

void Worker::work(Job job) {
  return;
}

void Worker::handle_message(network::Message message) {
  if(strcmp(message.data, network::Server::CONNECTED_MESSAGE) == 0) {
    network::write({
      .handle = message.handle,
      .data = network::Server::REGISTER_WORKER_MESSAGE,
      .length = strlen(network::Server::REGISTER_WORKER_MESSAGE)
    });
  } else {
    // work
    return;
  }
}

network::Client* Worker::get_network_client() {
  return network_client;
}


} }
