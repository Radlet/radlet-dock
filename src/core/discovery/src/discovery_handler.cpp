// std lib
#include <iostream>
#include <vector>

// protos
#include "device.pb.h"

// internal modules
#include "http_interface.h"
#include "temporary_data_interface.h"
#include "log.h"

// implementation file
#include "discovery_handler.h"

core::discovery::DiscoveryHandler::DiscoveryHandler() {}

void core::discovery::DiscoveryHandler::handleDiscoveryData(std::string ip,
                                                            std::string port,
                                                            std::string mac) {

  auto device = radlet_dock::device::Device();
  device.set_id(mac);
  device.set_name(ip);
  database::TemporaryDataInterface::add(device);
  log_info("Device discovery successful");
  log_warning("Device data: " + device.DebugString());
  // io::adaptor::tcp_interface::HttpSender::requestAttach(ip, port, mac);
}