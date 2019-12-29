#ifndef LATTICE_HUB_CORE_DB_DB_INTERFACE_H
#define LATTICE_HUB_CORE_DB_DB_INTERFACE_H

#include "sqlite3pp.h"

namespace database {
class DeviceDbInterface;
class UserDbInterface;
} // namespace database

class database::DeviceDbInterface {
  void addDevice();
  void updateDevice();
  void removeDevice();
};

class database::UserDbInterface {
  void addUser();
  void updateUser();
  void removeUser();
};

#endif // LATTICE_HUB_CORE_DB_DB_INTERFACE_H