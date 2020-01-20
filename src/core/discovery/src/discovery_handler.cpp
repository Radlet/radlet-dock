// std lib
#include <iostream>
#include <vector>

// 3rd party lib
// #include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// internal modules
#include "http_interface.h"

// implementation file
#include "discovery_handler.h"

core::discovery::DiscoveryHandler::DiscoveryHandler() {}

void core::discovery::DiscoveryHandler::extract_message(
    std::string raw_message) {
  std::stringstream ss;
  ss << raw_message;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);

  io::adaptor::tcp_interface::HttpSender::requestAttach(
      pt.get<std::string>("ip"), pt.get<std::string>("port"),
      pt.get<std::string>("mac"));
}