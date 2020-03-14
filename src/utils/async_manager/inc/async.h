/**
 * @file async.h
 * @author humble_d
 * @brief Async function execution interface (singleton)
 * @version 0.1
 * @date 2020-03-10
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef RADLET_DOCK_UTILS_ASYNC_MANAGER
#define RADLET_DOCK_UTILS_ASYNC_MANAGER

// std
#include <iostream>

// 3rd party lib
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

#define THREAD_POOL_SIZE 12

class Async {
  static boost::shared_ptr<Async> instance;
  boost::asio::io_service io_service;
  boost::asio::io_service::work work;
  boost::thread_group threadPool;

  Async() : work(io_service) {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
      threadPool.create_thread(
          boost::bind(&Async::workerThread, this, &io_service));
    }
  }

  Async(Async &obj) : work(io_service) {}

  Async operator=(Async &rhs) {}

  void workerThread(boost::asio::io_service *io_service_ptr) {
    std::cout << "Worker thread started" << std::endl;
    io_service_ptr->run();
  }

public:
  /**
   * @brief Get the Instance object
   *
   * @return boost::shared_ptr<Async>
   */
  static boost::shared_ptr<Async> getInstance();

  /**
   * @brief get hold of the io service object directly
   *
   * @return boost::asio::io_service&
   */
  boost::asio::io_service &getIOServiceInstance();

  /**
   * @brief execute the method.
   *
   * @args func- function object to execute.
   */
   template<typename T>
   void execute(T func) {
     io_service.post(func);
   }
};

#endif
