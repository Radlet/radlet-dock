/**
 * @file discovery_handler.h
 * @author humble_D (humble.discipulus@gmail.com)
 * @brief Deals with pairing data, data cache, and DB calls
 * @version 0.1
 * @date 2020-01-22
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef LATTICE_HUB_CORE_DISCOVERY_HANDLER
#define LATTICE_HUB_CORE_DISCOVERY_HANDLER

#include <string>

namespace core {
namespace discovery {

/**
 * @brief A class for handling discovery related functions and data
 *
 */
class DiscoveryHandler;

} // namespace discovery
} // namespace core

class core::discovery::DiscoveryHandler {
  DiscoveryHandler();

public:
  /**
   * @brief This function is called in response to a UDP packet
   *        sent to the hub by a discoverable IOT device
   *
   * @param ip IP address of the IOT device
   * @param port Port number of TPC server of IOT device
   * @param mac Mac address of the IOT device
   */
  static void handleDiscoveryData(std::string ip, std::string port,
                                  std::string mac);
};

#endif