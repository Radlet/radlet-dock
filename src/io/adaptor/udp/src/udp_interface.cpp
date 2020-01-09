/**
 * @file udp_interface.cpp
 * @author humble_d
 * @brief 
 * @version 0.1
 * @date 2020-01-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// std lib
#include <iostream>

// lib
#include <boost/bind.hpp>

// implementation file
#include "udp_interface.h"

#define UDP_PORT 13000

io::adaptor::udp_interface::UdpReceiver::UdpReceiver(
    boost::shared_ptr<boost::asio::io_service> io_service,
    unsigned short multicast_port, std::string listener_ip,
    std::string multicast_ip)
    : socket_(*io_service) {
  // Create the socket so that multiple may be bound to the same address.
  udp::endpoint listen_endpoint(address::from_string(listener_ip),
                                multicast_port);
  socket_.open(listen_endpoint.protocol());
  socket_.set_option(udp::socket::reuse_address(true));
  socket_.bind(listen_endpoint);

  // Join the multicast group.
  socket_.set_option(multicast::join_group(address::from_string(multicast_ip)));

  // start listening to messages
  start_receive();
}

void io::adaptor::udp_interface::UdpReceiver::start_receive() {
  socket_.async_receive_from(
      boost::asio::buffer(data_, static_cast<int>(Message::MAX_LENGTH)),
      sender_endpoint_,
      boost::bind(
          &io::adaptor::udp_interface::UdpReceiver::UdpReceiver::handle_receive,
          this, boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

void io::adaptor::udp_interface::UdpReceiver::handle_receive(
    const boost::system::error_code &error, std::size_t bytes_transferred) {
  if (!error) {
    std::cout.write(data_, bytes_transferred);
    std::cout << std::endl;

    start_receive();
  }
}