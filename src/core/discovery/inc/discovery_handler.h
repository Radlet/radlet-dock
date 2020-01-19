#ifndef LATTICE_HUB_CORE_DISCOVERY_HANDLER
#define LATTICE_HUB_CORE_DISCOVERY_HANDLER

#include <string>

namespace core {
namespace discovery {
class DiscoveryHandler;
}
} // namespace core

class core::discovery::DiscoveryHandler{
public:
    DiscoveryHandler();
    static void extract_message( std::string raw_message );
};

#endif