#include <string>

namespace device {
  class DeviceManager;
}

class device::DeviceManager {
  int device_count;
  
public:
  // Constructor for DeviceManager.
  DeviceManager():device_count(0){}

  // Method invoked for adding a device.
  // TODO: Actual Implelemtation.
  void Add(std::string &ret);

  // Method invode for getting list of devices.
  // TODO: Formatting of output.
  void GetDevices(std::string &ret); 
};
