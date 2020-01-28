/**
 * @file db_interface.h
 * @author humble_D (humble.discipulus@gmail.com)
 * @brief sqlite3 interface class
 * @version 0.1
 * @date 2020-01-22
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef LATTICE_HUB_CORE_DB_PERSISTENT_DATA_INTERFACE
#define LATTICE_HUB_CORE_DB_PERSISTENT_DATA_INTERFACE

// stl
#include <string>

// 3rd party lib
#include "sqlite3pp.h"

namespace database {
/**
 * @brief A class for SQLite database interface
 *
 */
class DeviceDbInterface;
// class UserDbInterface;
} // namespace database

class database::DeviceDbInterface {
public:
  static sqlite3pp::database *db;

  /**
   * @brief Responsible for creating db object using the file
   *        path provided as argument
   *
   * @param db_file_path Path to sqlite file (file created relative to binary
   * path)
   * @return true
   * @return false
   */
  static bool connect(std::string db_file_path);

  /**
   * @brief Deletes the db object thus created using connect function
   *
   * @return true
   * @return false
   */
  static bool disconnect();

  /**
   * @brief Used to add an entry of the device data as part of
   *        registration process
   *
   * @param mac Mac address of the IOT device (used as unique id)
   * @param ip Ip address of the TCP server running on the IOT device
   * @param port Port of the TCP server running on the IOT device
   * @return true
   * @return false
   */
  static bool addDevice(std::string mac, std::string ip, std::string port);
  // void updateDevice();
  // void removeDevice();
};

// class database::UserDbInterface {
//   void addUser();
//   void updateUser();
//   void removeUser();
// };

#endif // LATTICE_HUB_CORE_DB_PERSISTENT_DATA_INTERFACE