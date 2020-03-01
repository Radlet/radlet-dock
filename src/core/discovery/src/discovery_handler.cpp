// std lib
#include <iostream>
#include <vector>

// protos
#include "device.pb.h"

// internal modules
#include "http_interface.h"
#include "log.h"
#include "temporary_data_interface.h"

// implementation file
#include "discovery_handler.h"

core::discovery::DiscoveryHandler::DiscoveryHandler() {}

void core::discovery::DiscoveryHandler::handleDiscoveryData(
    std::string id, std::string link, std::string type, std::string title,
    std::string description) {

  auto device = radlet_dock::device::Device();
  device.set_id(id);
  device.set_link(link);
  device.set_type(type);
  device.set_title(title);
  device.set_description(description);

  // log_warning("Discovered device data: " + device.DebugString());

  database::TemporaryDataInterface::add(device);
}

void core::discovery::DiscoveryHandler::attachDevice(std::string id) {
  auto device = radlet_dock::device::Device();
  device = database::TemporaryDataInterface::get(id);
  std::string link = device.link();
  
  io::adaptor::tcp_interface::HttpSender::requestAttach(id, link);
}