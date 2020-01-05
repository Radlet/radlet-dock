#ifndef LATTICE_HUB_IO_ADAPTOR_HTTP
#define LATTICE_HUB_IO_ADAPTOR_HTTP

// std lib
#include <string>

// lib
#include "crow_all.h"

namespace io::adaptor {
class Http;
}

class io::adaptor::Http {
  std::string api_output;
  crow::SimpleApp app;

public:
  Http();
  void listen();
};

#endif