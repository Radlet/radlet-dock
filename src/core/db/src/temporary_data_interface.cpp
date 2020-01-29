// std
#include <iostream>

// implementation file
#include "temporary_data_interface.h"

bool operator<(const lattice_hub::device::Device &device1,
          const lattice_hub::device::Device &device2) {
  return device1.id() < device2.id();
}

short_time_data::ShortTimeData<lattice_hub::device::Device>
    *database::TemporaryDataInterface::data_store = nullptr;

bool database::TemporaryDataInterface::connect() {
  data_store =
      new short_time_data::ShortTimeData<lattice_hub::device::Device>();
  std::cout << "temp db file created" << std::endl;
}

bool database::TemporaryDataInterface::disconnect() { delete data_store; }

bool database::TemporaryDataInterface::add(lattice_hub::device::Device device,
                                           int expiry_time) {
  try {
    data_store->Add(device, expiry_time);
    return true;
  } catch (...) {
    return false;
  }
}

lattice_hub::device::Device
database::TemporaryDataInterface::get(std::string key) {
  auto device = lattice_hub::device::Device();
  device.set_id(key);
  auto response = data_store->GetData(device);
  return response.second;
}

bool database::TemporaryDataInterface::remove(std::string key) {
  try {
    auto device = lattice_hub::device::Device();
    device.set_id(key);
    data_store->ForceDelete(device);
    return true;
  } catch (...) {
    return false;
  }
}