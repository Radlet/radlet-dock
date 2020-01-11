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

  app.port(8080).multithreaded().run();
}