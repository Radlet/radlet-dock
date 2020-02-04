#ifndef RADLET_DOCK_CORE_UTILS_THING_H
#define RADLET_DOCK_CORE_UTILS_THING_H

#include <boost/property_tree/ptree.hpp>

#include <string>

namespace thing {
class Thing;
}

class thing::Thing {
  boost::property_tree::ptree pt;

public:
  Thing();
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