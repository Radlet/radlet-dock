#include <iostream>
#include <fstream>

#include <boost/date_time.hpp>

#include "log.h"


using namespace std;

void lattice_log::Log::logger(
  const string &color,
  const string &file_name,
  const string &line_number,
  const string &data) {
 
  string info = color;

  if (timestamp_)
    info += to_iso_extended_string(boost::posix_time::second_clock::universal_time());

  if (file_name_)
    info += "[ " + file_name + " ]";

  if (line_number_)
    info += "[ " + line_number + " ] ";

  info += data + END_COLOR + "\n";
  log_file_ << info;
  log_file_.flush();

  if(std_out_)
    cout << info;
}

void lattice_log::Log::static_logger(
  const string &color,
  const string &file_name,
  const string &line_number,
  const string &data) {

  string info = color;
  info += to_iso_extended_string(boost::posix_time::second_clock::universal_time());
  info += "[ " + file_name + " ]";
  info += "[ " + line_number + " ] ";
  info += data + END_COLOR + "\n";
  lattice_log::Log::static_log_file_ << info;
  lattice_log::Log::static_log_file_.flush();

  cout << info;
}

ofstream lattice_log::Log::static_log_file_("server.txt",ios::app|ios::binary);
