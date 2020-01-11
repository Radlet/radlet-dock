// std lib
#include <iostream>
#include <vector>

// lib
#include <boost/algorithm/string.hpp> 

// implementation file
#include "discovery_handler.h"


core::discovery::DiscoveryHandler::DiscoveryHandler(){

}

void core::discovery::DiscoveryHandler::extract_message( std::string raw_message ){
    std::vector<std::string> data_array; 
    boost::split(data_array, raw_message, boost::is_any_of(" "));
    std::cout << "mac: " << data_array[0] << std::endl;
    std::cout << "ip: " << data_array[1] << std::endl;
}