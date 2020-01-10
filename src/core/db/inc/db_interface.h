#ifndef LATTICE_HUB_CORE_DB_DB_INTERFACE_H
#define LATTICE_HUB_CORE_DB_DB_INTERFACE_H

#include "sqlite3pp.h"

namespace core {
namespace db {
class DeviceDbInterface;
class UserDbInterface;
} // namespace db
} // namespace core

class core::db::DeviceDbInterface {
  void addDevice();
  void updateDevice();
  void removeDevice();
};

class core::db::UserDbInterface {
  void addUser();
  void updateUser();
  void removeUser();
};

#endif // LATTICE_HUB_CORE_DB_DB_INTERFACE_H