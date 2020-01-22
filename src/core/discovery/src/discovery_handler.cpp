// std lib
#include <iostream>
#include <vector>

// internal modules
#include "http_interface.h"

// implementation file
#include "discovery_handler.h"

core::discovery::DiscoveryHandler::DiscoveryHandler() {}

void core::discovery::DiscoveryHandler::handleDiscoveryData(std::string ip,
                                                            std::string port,
                                                            std::string mac) {

  // replace with cache mechanism
  io::adaptor::tcp_interface::HttpSender::requestAttach(ip, port, mac);
}