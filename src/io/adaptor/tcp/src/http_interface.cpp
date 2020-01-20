// stl
#include <iostream>

// 3rd party lib
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cpr/cpr.h>

// internal modules
#include "port_map.h"

// implementation file
#include "http_interface.h"

io::adaptor::tcp_interface::HttpReceiver::HttpReceiver() {}

void io::adaptor::tcp_interface::HttpReceiver::listen() {
  CROW_ROUTE(app, "/")([]() { return "Lattice deployed"; });

  CROW_ROUTE(app, "/attach")
      .methods("PUT"_method)(
          [&](const crow::request &req) { return api_output.c_str(); });

  CROW_ROUTE(app, "/devices")
      .methods("GET"_method)(
          [&](const crow::request &req) { return api_output.c_str(); });

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