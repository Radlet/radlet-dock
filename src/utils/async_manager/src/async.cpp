/**
 * @file async.cpp
 * @author humble_d
 * @brief Async function execution interface (singleton)
 * @version 0.1
 * @date 2020-03-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <async.h>

boost::shared_ptr<Async> Async::instance = nullptr;

boost::shared_ptr<Async> Async::getInstance(){
    if( instance == nullptr ){
        instance = boost::shared_ptr<Async>( new Async() );
    }
    return instance;
}

boost::asio::io_service & Async::getIOServiceInstance(){
    return io_service;
}
