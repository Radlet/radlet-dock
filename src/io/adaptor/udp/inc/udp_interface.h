#ifndef LATTICE_HUB_IO_ADAPTOR_UDP_INTERFACE
#define LATTICE_HUB_IO_ADAPTOR_UDP_INTERFACE

// stl
#include <string>

// libs
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

namespace io::adaptor::udp_interface {
using boost::asio::ip::udp;
using boost::asio::ip::address;

class UdpReceiver;
} // namespace io::adaptor::udp_interface

class io::adaptor::udp_interface::UdpReceiver {
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum class Message { MAX_LENGTH = 1024 };
  char data_[static_cast<int>(Message::MAX_LENGTH)];

  void start_receive();
  void handle_receive(const boost::system::error_code &, std::size_t);

public:
  UdpReceiver(boost::shared_ptr<boost::asio::io_service>, unsigned short,
              std::string, std::string);
};

#endif