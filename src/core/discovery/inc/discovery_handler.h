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

#ifndef RADLET_DOCK_CORE_DISCOVERY_HANDLER
#define RADLET_DOCK_CORE_DISCOVERY_HANDLER

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
   * @param id Unique ID of the IOT device (mac)
   * @param link Link to the device for TCP communication
   * @param type Type of IOT device
   * @param title Title of the device
   * @param description Textual description of the IOT device
   */
  static void handleDiscoveryData(std::string id, std::string link,
                                  std::string type, std::string title,
                                  std::string description);

  /**
   * @brief This function is called in response to node attachment
   *        request from the composer
   *
   * @param id The Node's unique id
   */
  static void attachDevice(std::string id);
};

#endif