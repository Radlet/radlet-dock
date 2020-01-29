// std
#include <iostream>

// implementation file
#include "persistent_data_interface.h"

sqlite3pp::database *database::DeviceDbInterface::db = nullptr;

bool database::DeviceDbInterface::connect(std::string db_file_path) {
  db = new sqlite3pp::database(db_file_path.c_str());

  std::cout << "db file created" << std::endl;
}

bool database::DeviceDbInterface::disconnect() { delete db; }

bool database::DeviceDbInterface::addDevice(std::string mac, std::string ip,
                                            std::string port) {
  sqlite3pp::command cmd(
      *db, "INSERT INTO devices (mac, ip, port) VALUES (?, ?, ?)");
  cmd.binder() << mac << ip << port;
  cmd.execute();

  std::cout << "device added successfully" << std::endl;
}