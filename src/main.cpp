// std lib
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

// boost imports
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

// proto
#include "thing_buffer.pb.h"
#include "user.pb.h"

// internal module
#include "http.h"
#include "port_map.h"
#include "udp_interface.h"

using namespace std;
using namespace boost::uuids;

void demo_user() {
  shared_ptr<lattice_hub::user::User> user1 =
      make_shared<lattice_hub::user::User>();
  // Generate random boost uuid, convert it to string-16 bytes and store.
  user1->set_id(boost::lexical_cast<string>(random_generator()()).c_str());
  user1->set_name("Lattic_hub_dummy_user");
  // Set current time as registered time.
  user1->set_registered_time(time(NULL));
  cout << user1->DebugString() << endl;
}

int main() {
  demo_user();

  // io::adaptor::Http http_listener;
  // http_listener.listen();

  try {
    boost::asio::io_service io_service;
    io::adaptor::udp_interface::UdpServer udpServer(io_service,
                                                    PortMap::UDP_PORT);
    io_service.run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
