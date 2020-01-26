#include <ctime>
#include <map>
#include <memory>
#include <utility>

#include "log.h"

using namespace std;

namespace short_time_data {

template<typename DataType>
class Comparator {
public:
  bool operator()(const shared_ptr<DataType> &data1, const shared_ptr<DataType> &data2) {
    return (*data1) < (*data2);
  }
};

// DataType should be comparable.
template<typename DataType>
class ShortTimeData {

  // Map of expiry time of data to Data objects.
  set<pair<long long, shared_ptr<DataType>>> expiry_data_map_;

  // Map of Data objects to expiry time.
  map<shared_ptr<DataType>, long long, Comparator<DataType>> data_time_map_;

public:

  bool operator()(const shared_ptr<DataType> &obj_1, const shared_ptr<DataType> &obj_2) const {
    return (*obj_1) < (*obj_2);
  }

  void Add(const DataType &data, int duration_secs = 30,
           long long init_time_secs = 0ll) {

    long long end_time_secs;
    long long current_time_secs = time(0);

    if (!init_time_secs) {
      end_time_secs = current_time_secs + duration_secs;
    } else {
      end_time_secs = init_time_secs + duration_secs;
    }

    shared_ptr<DataType> d_ptr = make_shared<DataType>(data);
    if (auto iter(data_time_map_.find(d_ptr)); iter != data_time_map_.end()){
      expiry_data_map_.erase({iter->second, iter->first});
      iter->second = end_time_secs;
      expiry_data_map_.insert({end_time_secs, iter->first});
      log_info("Already found data entry for item being added, updating expiry "
               "time.");
    } else {
      expiry_data_map_.insert({end_time_secs, d_ptr});
      data_time_map_.insert({d_ptr, end_time_secs});
      log_info("Creating new data entry.");
    }

    ExpiryCleanUp();
  }

  // This method cleans up any expired data items.
  void ExpiryCleanUp() {
    
    long long current_time_secs = time(0);

    // Erase all expired data items.
    while(expiry_data_map_.size() && expiry_data_map_.begin()->first < current_time_secs) {
      data_time_map_.erase(expiry_data_map_.begin()->second);
      expiry_data_map_.erase(expiry_data_map_.begin());
      log_warning("Erasing data entry.");
    }
  }

  void ForceDelete(const DataType &data) {

    auto d_ptr = make_shared<DataType>(data);

    if (auto iter (data_time_map_.find(d_ptr)); iter != data_time_map_.end()) {
      expiry_data_map_.erase({iter->second, iter->first});
      data_time_map_.erase(iter);
      log_info("Entry erase successful.");
    } else {
      log_warning("Data entry not found for removal.");
    }

    ExpiryCleanUp();
  }

  // GetData copy of stored data item.
  // Returns error_code, data object.
  // error_code 1 for success 0 otherwise.
  pair<int, DataType> GetData(const DataType &data) {
    ExpiryCleanUp();

    auto d_ptr = make_shared<DataType>(data);
    shared_ptr<DataType> ret = nullptr;
    if (auto iter (data_time_map_.find(d_ptr)); iter != data_time_map_.end()) {
      ret = iter->first;
    }

    return {ret!=nullptr, ret==nullptr?DataType():*ret};
  }
};

}
