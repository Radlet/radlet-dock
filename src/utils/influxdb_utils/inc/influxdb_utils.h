#ifndef LATTICE_HUB_INFLUXDB_UTILS
#define LATTICE_HUB_INFLUXDB_UTILS

#include <string>
#include <vector>

namespace influxdb {
  class InfluxDbUtils;
}

class influxdb::InfluxDbUtils {
  public:
  static std::vector<std::string> db_list;
  static std::string default_db;
  static std::vector<std::string> Query(const std::string &query);
  static void Add(const std::string &query);
};
#endif
