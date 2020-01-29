#ifndef LATTICE_HUB_UTILS_LOG
#define LATTICE_HUB_UTILS_LOG

// std
#include <fstream>
#include <string>

#define RED "\e[1;31m"
#define BLUE "\e[1;34m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define END_COLOR "\e[0m"

namespace lattice_log {

#define INFO(data) logger(BLUE, __FILE__, std::to_string(__LINE__), data)
#define ERROR(data) logger(RED, __FILE__, std::to_string(__LINE__), data)
#define SUCCESS(data) logger(GREEN, __FILE__, std::to_string(__LINE__), data)
#define log_info(data)                                                         \
  lattice_log::Log::static_logger(BLUE, __FILE__, std::to_string(__LINE__),    \
                                  data)
#define log_error(data)                                                        \
  lattice_log::Log::static_logger(RED, __FILE__, std::to_string(__LINE__), data)
#define log_success(data)                                                      \
  lattice_log::Log::static_logger(GREEN, __FILE__, std::to_string(__LINE__),   \
                                  data)
#define log_warning(data)                                                      \
  lattice_log::Log::static_logger(YELLOW, __FILE__, std::to_string(__LINE__),  \
                                  data)

class Log;
} // namespace lattice_log

class lattice_log::Log {
  std::ofstream log_file_;
  bool timestamp_, file_name_, line_number_, std_out_;
  std::string prefix_;

public:
  Log(const std::string &log_file = "log_file.out")
      : timestamp_(1), file_name_(1), line_number_(1), std_out_(1),
        log_file_(log_file.c_str(), std::ios::app | std::ios::binary) {}

  void logger(const std::string &color, const std::string &file_name,
              const std::string &line_number, const std::string &information);

  ~Log() { log_file_.close(); }

  // Static members
private:
  static std::ofstream static_log_file_;

public:
  static void static_logger(const std::string &color,
                            const std::string &file_name,
                            const std::string &line_number,
                            const std::string &information);
};

#endif
