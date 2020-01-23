#ifndef LATTICE_LOG
#define LATTICE_LOG
#include <fstream>
#include <string>

#define RED "\e[1;31m"
#define BLUE "\e[1;34m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define END_COLOR "\e[0m"

using namespace std;

namespace lattice_log {

#define INFO(data) logger(BLUE, __FILE__, std::to_string(__LINE__), data)
#define ERROR(data) logger(RED, __FILE__, std::to_string(__LINE__), data)
#define SUCCESS(data) logger(GREEN, __FILE__, std::to_string(__LINE__), data)
class Log {
  ofstream log_file_;
  bool timestamp_, file_name_, line_number_, std_out_;
  string prefix_;

public:
  Log(const string &log_file = "log_file.out"): 
    timestamp_(1),
    file_name_(1),
    line_number_(1),
    std_out_(1),
    log_file_(log_file.c_str(), ios::app | ios::binary) {}

  void logger(
    const string &color,
    const string &file_name,
    const string &line_number,
    const string &information);

  ~Log() { log_file_.close(); }
};
} // namespace lattice_log

#endif
