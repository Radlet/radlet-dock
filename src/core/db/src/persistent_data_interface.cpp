// std
#include <iostream>

// implementation file
#include "persistent_data_interface.h"

sqlite3pp::database *database::DeviceDbInterface::db = nullptr;

bool database::DeviceDbInterface::connect(std::string db_file_path) {
  db = new sqlite3pp::database(db_file_path.c_str());
  db->execute("CREATE TABLE devices ("
              "id TEXT PRIMARY KEY,"
              "link TEXT NOT NULL UNIQUE, type TEXT NOT NULL,"
              "title TEXT NOT NULL, description TEXT NOT NULL) ");

  std::cout << "db file created" << std::endl;
}

bool database::DeviceDbInterface::disconnect() { delete db; }

bool database::DeviceDbInterface::add(std::string id, std::string link,
                                      std::string type, std::string title,
                                      std::string description) {

  sqlite3pp::command cmd(*db, "INSERT INTO devices (id, link, type, title, "
                              "description) VALUES (?, ?, ?, ?, ?)");
  cmd.binder() << id << link << type << title << description;
  cmd.execute();
  return true;
}

std::vector<radlet_dock::device::Device> database::DeviceDbInterface::getAll() {
  std::vector<radlet_dock::device::Device> device_vector;

  sqlite3pp::query qry(
      *db, "SELECT id, link, type, title, description FROM devices");

  for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
    int j = 0;
    std::string id = (*i).get<char const *>(j++);
    std::string link = (*i).get<char const *>(j++);
    std::string type = (*i).get<char const *>(j++);
    std::string title = (*i).get<char const *>(j++);
    std::string description = (*i).get<char const *>(j++);

    auto device = radlet_dock::device::Device();
    device.set_id(id);
    device.set_link(link);
    device.set_type(type);
    device.set_title(title);
    device.set_description(description);

    device_vector.push_back(device);
  }

  return device_vector;
}

radlet_dock::device::Device database::DeviceDbInterface::get(std::string id) {
  std::string query =
      "SELECT id, link, type, title, description FROM devices WHERE id = \"";
  query += id;
  query += "\"";

  sqlite3pp::query qry(*db, query.c_str());

  auto device = radlet_dock::device::Device();
  for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
    int j = 0;
    std::string id = (*i).get<char const *>(j++);
    std::string link = (*i).get<char const *>(j++);
    std::string type = (*i).get<char const *>(j++);
    std::string title = (*i).get<char const *>(j++);
    std::string description = (*i).get<char const *>(j++);

    device.set_id(id);
    device.set_link(link);
    device.set_type(type);
    device.set_title(title);
    device.set_description(description);
  }

  return device;
}

bool database::DeviceDbInterface::remove(std::string id) {
  sqlite3pp::command cmd(*db, "DELETE FROM devices WHERE id = ?");
  cmd.binder() << id;
  cmd.execute();

  return true;
}
