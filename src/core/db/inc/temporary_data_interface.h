#ifndef LATTICE_HUB_CORE_DB_TEMPORARY_DATA_INTERFACE
#define LATTICE_HUB_CORE_DB_TEMPORARY_DATA_INTERFACE

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
  static short_time_data::ShortTimeData<lattice_hub::device::Device>
      *data_store;

public:
  static bool connect();
  static bool disconnect();
  static bool add(lattice_hub::device::Device device, int expiry_time = 3);
  lattice_hub::device::Device get(std::string key);
  // lattice_hub::device::Device get(lattice_hub::device::Device device);
  static std::vector<lattice_hub::device::Device> getAll();
  static bool remove(std::string key);
  // lattice_hub::device::Device remove(lattice_hub::device::Device device);
  static bool removeAll();
};

#endif