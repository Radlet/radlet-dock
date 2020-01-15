#include "iostream"

#include "cpr/cpr.h"
#include "influxdb_utils.h"

// Method to query from InfluxDB.
std::vector<std::string> influxdb::InfluxDbUtils::Query(const std::string &query) {
  std::cout << "Influx db query" << query << "\n";
  std::vector<std::string> results;
  auto r = cpr::Get(cpr::Url{"localhost:8086/query"},
                    cpr::Parameters{{"db", influxdb::InfluxDbUtils::default_db},
                                    {"q", query}});
  if (r.status_code != 200) {
    std::cout << "Error in quering InfluxDB\n";
    return results;
  }

  r.header["content-type"]; // application/json; charset=utf-8
  std::cout << "DB response " << r.text;

  // Create a parser method.
  results.push_back(r.text);
  return results;
}

void influxdb::InfluxDbUtils::Add(const std::string &query) {
  std::cout << "Pushing entry into influx db" << query;
}

std::string influxdb::InfluxDbUtils::default_db = "lattice_data";
std::vector<std::string> influxdb::InfluxDbUtils::db_list = std::vector<std::string>();
