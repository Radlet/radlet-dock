// std
#include "iostream"

// 3rd party lib
#include "cpr/cpr.h"

// implemented file
#include "sensor_data_interface.h"

// Add database with name db_name.
int database::SensorDataInterface::AddDatabase(const std::string &db_name) {

  auto query = "create database " + db_name;
  auto response = cpr::Post(cpr::Url{"localhost:8086/query"},
                            cpr::Parameters{{"q", query}});

  if (response.status_code != 200) {
    std::cout << "Error in creating database.\n";
    return 0;
  }

  response.header["content-type"]; // application/json; charset=utf-8
  std::cout << "DB response: " << response.text;

  if (database::SensorDataInterface::db_list.size() == 0) {
    database::SensorDataInterface::default_db = db_name;
  }

  if (std::find(database::SensorDataInterface::db_list.begin(),
                database::SensorDataInterface::db_list.end(),
                db_name) == database::SensorDataInterface::db_list.end()) {
    database::SensorDataInterface::db_list.push_back(db_name);
  }

  return 1;
}

// Method to query from Sensor Data.
std::vector<std::string>
database::SensorDataInterface::Query(const std::string &query) {
  std::cout << "Influx db query: " << query << ".\n";
  std::vector<std::string> results;
  auto response = cpr::Get(
      cpr::Url{"localhost:8086/query"},
      cpr::Parameters{{"db", database::SensorDataInterface::default_db},
                      {"q", query}});
  if (response.status_code != 200) {
    std::cout << "Error in quering InfluxDB.\n";
    return results;
  }

  response.header["content-type"]; // application/json; charset=utf-8
  std::cout << "DB response " << response.text ;

  // TODO: Use JSON parser.
  results.push_back(response.text);
  return results;
}

void database::SensorDataInterface::Add(const std::string &query) {
  std::cout << "Pushing entry into influx db" << query << ".\n";
}

int database::SensorDataInterface::RecordDeviceData(
    const std::string &device_id, const std::string &device_data_id,
    const std::string &device_data, const std::string &time_stamp) {

  // Returns True if write successful.
  std::cout << "Pushing data " << device_id << " " << device_data_id << " "
            << device_data << " " << time_stamp << ".\n";

  auto query = "device_data,id=\"" + device_id + "\",data_id=\"" +
               device_data_id + "\" data=\"" + device_data + "\" " + time_stamp;
  auto response = cpr::Post(
      cpr::Url{("localhost:8086/write?db=" +
                database::SensorDataInterface::default_db + "&precision=ms")
                   .c_str()},
      cpr::Body{query.c_str()}, cpr::Header{{"Content-Type", "text/plain"}});

  if (response.status_code != 204) {
    std::cout << "Error in writing data.\n";
    return 0;
  }
  return 1;
}

std::vector<std::string>
database::SensorDataInterface::GetDeviceData(const std::string &device_id) {

  auto query = "select * from device_data where id='\"" + device_id + "\"'";
  auto response = cpr::Get(
      cpr::Url{"localhost:8086/query"},
      cpr::Parameters{{"db", database::SensorDataInterface::default_db},
                      {"q", query}});
  std::vector<std::string> results;
  if (response.status_code != 200) {
    std::cout << "Error in quering InfluxDB\n";
    return results;
  }

  response.header["content-type"]; // application/json; charset=utf-8
  std::cout << "DB response " << response.text ;

  // TODO: Use JSON parser.
  results.push_back(response.text);
  return results;
}

std::string database::SensorDataInterface::default_db = "radlet_data";
std::vector<std::string> database::SensorDataInterface::db_list =
    std::vector<std::string>();
