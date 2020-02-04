#include <fstream>
#include <iostream>

#include <boost/date_time.hpp>

#include "log.h"

void radlet_log::Log::logger(const std::string &color,
                              const std::string &file_name,
                              const std::string &line_number,
                              const std::string &data) {

  std::string info = color;

  if (timestamp_)
    info += to_iso_extended_string(
        boost::posix_time::second_clock::universal_time());

  if (file_name_)
    info += "[ " + file_name + " ]";

  if (line_number_)
    info += "[ " + line_number + " ] ";

  info += data + END_COLOR + "\n";
  log_file_ << info;
  log_file_.flush();

  if (std_out_)
    std::cout << info;
}

void radlet_log::Log::static_logger(const std::string &color,
                                     const std::string &file_name,
                                     const std::string &line_number,
                                     const std::string &data) {

  std::string info = color;
  info +=
      to_iso_extended_string(boost::posix_time::second_clock::universal_time());
  info += "[ " + file_name + " ]";
  info += "[ " + line_number + " ] ";
  info += data + END_COLOR + "\n";
  radlet_log::Log::static_log_file_ << info;
  radlet_log::Log::static_log_file_.flush();

  std::cout << info;
}

std::ofstream radlet_log::Log::static_log_file_("server.txt",
                                                 std::ios::app |
                                                     std::ios::binary);
