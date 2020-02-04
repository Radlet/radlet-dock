#ifndef RADLET_DOCK_SENSOR_DI
#define RADLET_DOCK_SENSOR_DI

#include <string>
#include <vector>

namespace database {
class SensorDataInterface;
}

class database::SensorDataInterface {
public:
  static std::vector<std::string> db_list;
  static std::string default_db;
  static std::vector<std::string> Query(const std::string &query);
  static void Add(const std::string &query);
  static int RecordDeviceData(const std::string &device_id,
                              const std::string &data_id,
                              const std::string &device_data,
                              const std::string &time_stamp = "");
  static std::vector<std::string> GetDeviceData(const std::string &device_id);
  static int AddDatabase(const std::string &db_name);
};
#endif
