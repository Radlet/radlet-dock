// stl
#include <iostream>
#include <vector>

// 3rd party lib
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cpr/cpr.h>

// proto
#include "device.pb.h"

// internal modules
#include "discovery_handler.h"
#include "port_map.h"
#include "temporary_data_interface.h"

// implementation file
#include "http_interface.h"

io::adaptor::tcp_interface::HttpReceiver::HttpReceiver() {}

void io::adaptor::tcp_interface::HttpReceiver::listen() {
  CROW_ROUTE(app, "/")([]() { return "Lattice deployed"; });

  CROW_ROUTE(app, "/attachdevice")
      .methods("POST"_method)([&](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x)
          return crow::response(400);

        std::string id = x["id"].s();
        core::discovery::DiscoveryHandler::attachDevice(id);

        return crow::response("Attachment request recieved");
      });

  CROW_ROUTE(app, "/getavailabledevices")
      .methods("GET"_method)([&](const crow::request &req) {
        std::vector<radlet_dock::device::Device> device_list =
            database::TemporaryDataInterface::getAll();
        crow::json::wvalue response_data;

        boost::property_tree::ptree pt;
        boost::property_tree::ptree device_info_array;

        std::stringstream ss;
        for (int i = 0; i < device_list.size(); i++) {
          boost::property_tree::ptree device_info;
          device_info.put("id", device_list[i].id());
          device_info.put("type", device_list[i].type());
          device_info.put("title", device_list[i].title());
          device_info.put("description", device_list[i].description());
          device_info_array.push_back(std::make_pair("", device_info));
        }
        pt.add_child("devices", device_info_array);
        boost::property_tree::json_parser::write_json(ss, pt);

        return crow::response(ss.str());
      });

  app.port(PortMap::TCP_HTTP_PORT).multithreaded().run();
}

bool io::adaptor::tcp_interface::HttpSender::requestAttach(std::string id,
                                                           std::string link) {

  boost::property_tree::ptree pt;
  std::string dock_link_prefix = "http://192.168.100.2:";
  pt.put("dock_link",
         dock_link_prefix + std::to_string(PortMap::TCP_HTTP_PORT));
  pt.put("id", id);

  std::stringstream ss;
  boost::property_tree::json_parser::write_json(ss, pt);

  auto request = cpr::Post(cpr::Url{link + "/attach"}, cpr::Body{ss.str()});

  std::cout << request.header["content-type"]
            << std::endl; // application/json; charset=utf-8
  std::cout << request.status_code << std::endl;
  std::cout << request.text << std::endl;
}