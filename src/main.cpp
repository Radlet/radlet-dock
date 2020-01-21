// std lib
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

// boost imports
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

// proto
#include "thing_buffer.pb.h"
#include "user.pb.h"

// internal module
#include "ip_map.h"
#include "port_map.h"
#include "http_interface.h"
#include "udp_interface.h"
#include "sensor_data_interface.h"
#include "db_interface.h"

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

  // SensorDI demo
  sensor_data_interface::SensorDI::AddDatabase("sensor_db");
  sensor_data_interface::SensorDI::Query("select * from device_data");
  sensor_data_interface::SensorDI::RecordDeviceData("d3:3e:af", "001d2s", "somedata");
  sensor_data_interface::SensorDI::GetDeviceData("d3:3e:af");
}

void StartUdpServer() {
  cout << "Attempting to start Udp server\n";
  try {
    boost::shared_ptr<boost::asio::io_service> io_service(
        new boost::asio::io_service);

    // start udp receiver
    io::adaptor::udp_interface::UdpReceiver udpReceiver(
        io_service, PortMap::UDP_MULTICAST_PORT, IpMap::UDP_LISTENER,
        IpMap::UDP_MULTICAST);

    io_service->run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void StartTcpServer() {
  cout << "Attempting to start Tcp server\n";
  io::adaptor::tcp_interface::HttpReceiver httpReceiver;
  httpReceiver.listen();
}

int main() {
  demo_user();
  database::DeviceDbInterface::connect("device.db");

  boost::thread_group worker_threads;
  worker_threads.create_thread(StartUdpServer);
  worker_threads.create_thread(StartTcpServer);
  cout << "Servers started in separate threads\n";
  worker_threads.join_all();

  database::DeviceDbInterface::disconnect();
  return 0;
}
