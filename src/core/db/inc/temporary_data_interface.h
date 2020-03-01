#ifndef RADLET_DOCK_CORE_DB_TEMPORARY_DATA_INTERFACE
#define RADLET_DOCK_CORE_DB_TEMPORARY_DATA_INTERFACE

// std
#include <string>
#include <vector>

// protos
#include "device.pb.h"

// internal module
#include "short_time_data.h"

namespace database {
class TemporaryDataInterface;
}

class database::TemporaryDataInterface {
  static short_time_data::ShortTimeData<radlet_dock::device::Device>
      *data_store;

public:
  static bool connect();
  static bool disconnect();
  static bool add(radlet_dock::device::Device device, int expiry_time = 5);
  static radlet_dock::device::Device get(std::string key);
  // radlet_dock::device::Device get(radlet_dock::device::Device device);
  static std::vector<radlet_dock::device::Device> getAll();
  static bool remove(std::string key);
  // radlet_dock::device::Device remove(radlet_dock::device::Device device);
  static bool removeAll();
};

#endif