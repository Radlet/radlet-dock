#ifndef LATTICE_HUB_UTILS_IP_MAP
#define LATTICE_HUB_UTILS_IP_MAP

#include <string>

class IpMap {
public:
  static const std::string UDP_LISTENER;
  static const std::string UDP_MULTICAST;
};

const std::string IpMap::UDP_LISTENER = "0.0.0.0";
const std::string IpMap::UDP_MULTICAST = "239.255.0.1";

#endif