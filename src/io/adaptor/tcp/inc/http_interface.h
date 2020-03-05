/**
 * @file http_interface.h
 * @author humble_D (humble.discipulus@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-01-22
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef RADLET_DOCK_IO_ADAPTOR_HTTP_INTERFACE
#define RADLET_DOCK_IO_ADAPTOR_HTTP_INTERFACE

// stl
#include <string>

// lib
#include "crow_all.h"
#include <boost/asio.hpp>

namespace io {
namespace adaptor {
namespace tcp_interface {

/**
 * @brief A class for receiving HTTP data
 *
 */
class HttpReceiver;

/**
 * @brief A class for sending HTTP data
 *
 */
class HttpSender;

} // namespace tcp_interface
} // namespace adaptor
} // namespace io

class io::adaptor::tcp_interface::HttpReceiver {
  std::string api_output;
  crow::SimpleApp app;

public:
  HttpReceiver();
  void listen();
};

class io::adaptor::tcp_interface::HttpSender {
public:
  /**
   * @brief The function sends hub data to the attach API exposed by
   *        the IOT device. The information exchanged is used for
   *        duplex communication.
   *
   * @param id ID of the node device
   * @param link TCP link to the node device
   * @return true
   * @return false
   */
  static bool requestAttach(std::string id, std::string link );

  /**
   * @brief The function sends a request to the detach API exposed by
   *        the IOT device. On successful detachment, the device is removed
   *        from persistant DB.
   *
   * @param id ID of the node device
   * @param link TCP link to the node device
   * @return true
   * @return false
   */
  static bool requestDetach(std::string id, std::string link );
};

#endif