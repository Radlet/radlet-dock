#ifndef LATTICE_HUB_CORE_DB_DB_INTERFACE
#define LATTICE_HUB_CORE_DB_DB_INTERFACE

// stl
#include <string>

// 3rd party lib
#include "sqlite3pp.h"

namespace database {
class DeviceDbInterface;
// class UserDbInterface;
} // namespace database

class database::DeviceDbInterface {
public:
  static sqlite3pp::database *db;

  static bool connect(std::string db_file_path);
  static bool disconnect();
  static bool addDevice(std::string mac, std::string ip, std::string port);
  // void updateDevice();
  // void removeDevice();
};

// class database::UserDbInterface {
//   void addUser();
//   void updateUser();
//   void removeUser();
// };

#endif // LATTICE_HUB_CORE_DB_DB_INTERFACE