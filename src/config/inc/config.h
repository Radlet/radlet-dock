#ifndef RADLET_DOCK_CONFIG
#define RADLET_DOCK_CONFIG

#include <string>

namespace config {
class IpMap;
class PortMap;
}

class config::IpMap {
public:
  static const std::string UDP_LISTENER;
  static const std::string UDP_MULTICAST;
};

class config::PortMap{
	public:
	static const unsigned short UDP_MULTICAST_PORT;
	static const unsigned short TCP_HTTP_PORT;
};

#endif