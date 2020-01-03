#ifndef LATTICE_HUB_IO_ADAPTOR_UDP_INTERFACE
#define LATTICE_HUB_IO_ADAPTOR_UDP_INTERFACE

// libs
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace io::adaptor::udp_interface {
using boost::asio::ip::udp;

class UdpServer;
} // namespace io::adaptor::udp_interface

class io::adaptor::udp_interface::UdpServer {
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 1> recv_buffer_;

  void start_receive();
  void handle_receive(const boost::system::error_code &, std::size_t);
  void handle_send(boost::shared_ptr<std::string>,
                   const boost::system::error_code &, std::size_t);

public:
  UdpServer(boost::asio::io_service &, unsigned short);
};

#endif