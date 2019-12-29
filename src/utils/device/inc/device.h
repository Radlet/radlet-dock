#ifndef LATTICE_HUB_CORE_UTILS_DEVICE_H
#define LATTICE_HUB_CORE_UTILS_DEVICE_H

#include <boost/property_tree/ptree.hpp>

#include <string>

namespace device {
class Device;
}

class device::Device {
  boost::property_tree::ptree pt;

public:
  Device();
  // id
  // title
  // description
  // property[]
  // action[]
  // event[]
};

// class Property
// {
// 	// type
// 	// title
// 	// description
// 	// maximum (based on type)
// 	// minimum (based on type)
// };

// class Action
// {
// 	// title
// 	// description
// 	//
// };

// class Event
// {
// 	// title
// 	// type
// 	// description
// };

#endif