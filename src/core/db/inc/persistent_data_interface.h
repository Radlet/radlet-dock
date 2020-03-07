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

#ifndef RADLET_DOCK_CORE_DB_PERSISTENT_DATA_INTERFACE
#define RADLET_DOCK_CORE_DB_PERSISTENT_DATA_INTERFACE

// stl
#include <string>
#include <vector>

// 3rd party lib
#include "sqlite3pp.h"

// protos
#include "device.pb.h"

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
   * @param id Unique ID of the IOT device (mac)
   * @param link Link to the device for TCP communication
   * @param type Type of IOT device
   * @param title Title of the device
   * @param description Textual description of the IOT device
   * @return true
   * @return false
   */
  static bool add(std::string id, std::string link, std::string type,
                  std::string title, std::string description);

  /**
   * @brief Used to get a the list of nodes registered to the doc
   *
   * @return std::vector<radlet_dock::device::Device>
   */
  static std::vector<radlet_dock::device::Device> getAll();

  /**
   * @brief Used to get back a Device proto that matches the id
   *
   * @param id Unique ID of the Node
   * @return radlet_dock::device::Device
   */
  static radlet_dock::device::Device get(std::string id);

  // void updateDevice();

  /**
   * @brief Used to remove an entry of the device data as part of
   *        registration process
   *
   * @param id Unique ID of the IOT device (mac)
   * @return true
   * @return false
   */
  static bool remove(std::string id);
};

// class database::UserDbInterface {
//   void addUser();
//   void updateUser();
//   void removeUser();
// };

#endif // RADLET_DOCK_CORE_DB_PERSISTENT_DATA_INTERFACE