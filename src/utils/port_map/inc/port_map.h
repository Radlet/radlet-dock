#ifndef LATTICE_HUB_UTILS_PORT_MAP
#define LATTICE_HUB_UTILS_PORT_MAP

#include <string>

class PortMap{
	public:
	static const unsigned short UDP_MULTICAST_PORT;
};

const unsigned short PortMap::UDP_MULTICAST_PORT = 30001;

#endif