// std
#include <iostream>

// implementation file
#include "temporary_data_interface.h"

bool operator<(const radlet_dock::device::Device &device1,
               const radlet_dock::device::Device &device2) {
  return device1.id() < device2.id();
}

short_time_data::ShortTimeData<radlet_dock::device::Device>
    *database::TemporaryDataInterface::data_store = nullptr;

bool database::TemporaryDataInterface::connect() {
  data_store =
      new short_time_data::ShortTimeData<radlet_dock::device::Device>();
}

bool database::TemporaryDataInterface::disconnect() { delete data_store; }

bool database::TemporaryDataInterface::add(radlet_dock::device::Device device,
                                           int expiry_time) {
  try {
    data_store->Add(device, expiry_time);
    return true;
  } catch (...) {
    return false;
  }
}

radlet_dock::device::Device
database::TemporaryDataInterface::get(std::string key) {
  auto device = radlet_dock::device::Device();
  device.set_id(key);
  auto response = data_store->GetData(device);
  return response.second;
}

std::vector<radlet_dock::device::Device>
database::TemporaryDataInterface::getAll() {
  vector<radlet_dock::device::Device> device_vector = data_store->GetAll();
  return device_vector;
}

bool database::TemporaryDataInterface::remove(std::string key) {
  try {
    auto device = radlet_dock::device::Device();
    device.set_id(key);
    data_store->ForceDelete(device);
    return true;
  } catch (...) {
    return false;
  }
}