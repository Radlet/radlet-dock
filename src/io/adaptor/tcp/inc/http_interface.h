#ifndef LATTICE_HUB_IO_ADAPTOR_HTTP_INTERFACE
#define LATTICE_HUB_IO_ADAPTOR_HTTP_INTERFACE

// stl
#include <string>

// lib
#include "crow_all.h"
#include <boost/asio.hpp>
// #include <boost/beast.hpp>

namespace io {
namespace adaptor {
namespace tcp_interface {

class HttpReceiver;
class HttpSender;

}
}
}

class io::adaptor::tcp_interface::HttpReceiver {
  std::string api_output;
  crow::SimpleApp app;

public:
  HttpReceiver();
  void listen();
};

class io::adaptor::tcp_interface::HttpSender{
  public:
  static bool requestAttach(std::string ip, std::string port, std::string mac);
};

#endif