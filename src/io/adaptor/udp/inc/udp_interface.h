/**
 * @file udp_interface.h
 * @author humble_d (humble.discipulus@gmail.com)
 * @brief UDP interface classes ( listener )
 * @version 0.1
 * @date 2020-01-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef RADLET_DOCK_IO_ADAPTOR_UDP_INTERFACE
#define RADLET_DOCK_IO_ADAPTOR_UDP_INTERFACE

// stl
#include <string>

// 3rd party libs
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

namespace io {
namespace adaptor {
namespace udp_interface {

using namespace boost::asio::ip;

/**
 * @brief A class for receiving UDP broadcast packets
 *
 */
class UdpReceiver;

} // namespace udp_interface
} // namespace adaptor
} // namespace io

class io::adaptor::udp_interface::UdpReceiver {
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum class Message { MAX_LENGTH = 1024 };
  char data_[static_cast<int>(Message::MAX_LENGTH)];

  /**
   * @brief Starts the udp receiver
   *
   */
  void start_receive();

  /**
   * @brief on receiving a message from sender execute handler
   *
   * @param error Boost error object
   * @param bytes_transferred Number of bytes received
   */
  void handle_receive(const boost::system::error_code &error,
                      std::size_t bytes_transferred);

public:
  /**
   * @brief Construct a new Udp Receiver object
   *
   * @param io_service io_service object
   * @param multicast_port UDP port that the host exposes
   * @param listener_ip IP address to which the listener will be bound to
   * @param multicast_ip The class D Ip that marks the multicast group
   */
  UdpReceiver(boost::asio::io_service &io_service,
              unsigned short multicast_port, std::string listener_ip,
              std::string multicast_ip);
};

#endif