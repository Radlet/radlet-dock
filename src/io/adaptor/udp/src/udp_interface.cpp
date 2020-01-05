// std lib
#include <iostream>
#include <thread>

// lib
#include <boost/bind.hpp>

// implementation file
#include "udp_interface.h"

#define UDP_PORT 13000

io::adaptor::udp_interface::UdpServer::UdpServer(
    boost::asio::io_service &io_service, unsigned short port)
    : socket_(io_service, udp::endpoint(udp::v4(), port)) {
  start_receive();
}

void io::adaptor::udp_interface::UdpServer::start_receive() {
  socket_.async_receive_from(
      boost::asio::buffer(recv_buffer_), remote_endpoint_,
      boost::bind(&io::adaptor::udp_interface::UdpServer::handle_receive, this, boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void io::adaptor::udp_interface::UdpServer::handle_receive(
    const boost::system::error_code &error, std::size_t bytes_transferred) {
  if (!error || error == boost::asio::error::message_size) {
    boost::shared_ptr<std::string> message(new std::string("Test string"));

    socket_.async_send_to(
        boost::asio::buffer(*message), remote_endpoint_,
        boost::bind(&io::adaptor::udp_interface::UdpServer::handle_send, this, message,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));

    start_receive();
  }
}

void io::adaptor::udp_interface::UdpServer::handle_send(
    boost::shared_ptr<std::string> message,
    const boost::system::error_code &error, std::size_t bytes_transferred) {}