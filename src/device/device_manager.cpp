
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include "device_manager.h"

using namespace boost;
using namespace device;
using namespace std;

// ret is the result of API.
void DeviceManager::Add(string &ret) {
  device_count++;
  ret="Success";
}

// ret is the result of API.
void DeviceManager::GetDevices(string &ret) {
   ret = move(lexical_cast<string>(device_count)) ;
}
