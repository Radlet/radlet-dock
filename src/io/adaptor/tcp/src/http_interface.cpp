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
#include "port_map.h"
#include "temporary_data_interface.h"

// implementation file
#include "http_interface.h"

io::adaptor::tcp_interface::HttpReceiver::HttpReceiver() {}

void io::adaptor::tcp_interface::HttpReceiver::listen() {
  CROW_ROUTE(app, "/")([]() { return "Lattice deployed"; });

  CROW_ROUTE(app, "/attach")
      .methods("GET"_method)([&](const crow::request &req) {
        // io::adaptor::tcp_interface::HttpSender::requestAttach(ip, port, mac);
        std::cout << api_output.c_str() << std::endl;
        return api_output.c_str();
      });

  CROW_ROUTE(app, "/getavailabledevices")
      .methods("GET"_method)([&](const crow::request &req) {
        std::vector<radlet_dock::device::Device> device_list =
            database::TemporaryDataInterface::getAll();

        std::cout << device_list.size() << std::endl;
        crow::json::wvalue response_data;

        boost::property_tree::ptree pt;
        boost::property_tree::ptree device_info_array;

        std::stringstream ss;
        for (int i = 0; i < device_list.size(); i++) {
          boost::property_tree::ptree device_info;
          device_info.put("id", device_list[i].id());
          device_info.put("name", device_list[i].name());
          device_info_array.push_back(std::make_pair("", device_info));
        }
        pt.add_child("deviceArray", device_info_array);
        boost::property_tree::json_parser::write_json(ss, pt);

        return crow::response(ss.str());
      });

  app.port(PortMap::TCP_HTTP_PORT).multithreaded().run();
}

bool io::adaptor::tcp_interface::HttpSender::requestAttach(std::string ip,
                                                           std::string port,
                                                           std::string mac) {
  boost::property_tree::ptree pt;
  pt.put("ip", "111.111.111.111");
  pt.put("mac", mac);
  pt.put("port", PortMap::TCP_HTTP_PORT);

  std::stringstream ss;
  boost::property_tree::json_parser::write_json(ss, pt);

  auto request = cpr::Post(cpr::Url{"http://" + ip + ":" + port + "/attach"},
                           cpr::Body{ss.str()});

  std::cout << request.header["content-type"]
            << std::endl; // application/json; charset=utf-8
  std::cout << request.status_code << std::endl;
  std::cout << request.text << std::endl;
}