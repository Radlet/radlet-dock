// std lib
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

// 3rd party imports
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
#include "device.pb.h"

// internal module
#include "http_interface.h"
#include "udp_interface.h"
#include "port_map.h"
#include "ip_map.h"
#include "persistent_data_interface.h"
#include "sensor_data_interface.h"
#include "temporary_data_interface.h"
#include "log.h"

using namespace std;
using namespace boost::uuids;

// logger initiated for main.cpp
lattice_log::Log Logger("main.txt");

bool operator<(const lattice_hub::user::User &user1,
               const lattice_hub::user::User &user2) {
  return user1.id() < user2.id();
}

// void demo_user() {
//   shared_ptr<lattice_hub::user::User> user1 =
//       make_shared<lattice_hub::user::User>();
//   // Generate random boost uuid, convert it to string-16 bytes and store.
//   user1->set_id(boost::lexical_cast<string>(random_generator()()).c_str());
//   user1->set_name("Lattic_hub_dummy_user");
//   // Set current time as registered time.
//   user1->set_registered_time(time(NULL));
//   cout << user1->DebugString() << endl;

//   // SensorDataInterface demo
//   database::SensorDataInterface::Query("select * from device_data");
//   database::SensorDataInterface::RecordDeviceData("d3:3e:af", "001d2s",
//                                                   "somedata");
//   database::SensorDataInterface::GetDeviceData("d3:3e:af");

//   // Logger
//   lattice_log::Log L("dummy.txt");
//   L.INFO("something");
//   L.ERROR("something terrible");
//   L.SUCCESS("Threat eliminated");

//   log_info("Server start initiated successfully.");

//   short_time_data::ShortTimeData<lattice_hub::user::User> data_store;
//   auto user3 = lattice_hub::user::User();
//   user3.set_id("use3");
//   user3.set_name("use3");
//   data_store.Add(user3, 3);
//   auto user2 = lattice_hub::user::User();
//   user2.set_id("ef22");
//   data_store.Add(user2);
//   user2.set_id("use3");
//   auto resp = data_store.GetData(user2);
//   log_warning("Error Code : " + to_string(resp.first) +
//               "\nResponse: " + resp.second.DebugString());
//   sleep(4);
//   resp = data_store.GetData(user2);
//   log_error(to_string(resp.first));
//   data_store.ForceDelete(user3);
//   user2.set_id("ef22");
//   data_store.ForceDelete(user2);
// }

void StartUdpServer() {
  log_info("Attempting to start Udp server\n");
  try {
    boost::shared_ptr<boost::asio::io_service> io_service(
        new boost::asio::io_service);
    io::adaptor::udp_interface::UdpReceiver udpReceiver(
        io_service, PortMap::UDP_MULTICAST_PORT, IpMap::UDP_LISTENER,
        IpMap::UDP_MULTICAST);
    io_service->run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void StartTcpServer() {
  log_info("Attempting to start Tcp server\n");
  io::adaptor::tcp_interface::HttpReceiver httpReceiver;
  httpReceiver.listen();
}

int main() {
  log_info("Attempting to start DB service\n");
  database::DeviceDbInterface::connect("device.db");
  database::SensorDataInterface::AddDatabase("sensor_db");
  database::TemporaryDataInterface::connect();
  log_success("DB service started successfully\n");

  boost::thread_group worker_threads;
  worker_threads.create_thread(StartUdpServer);
  worker_threads.create_thread(StartTcpServer);
  
  log_success("Servers started in separate threads\n");
  worker_threads.join_all();

  database::DeviceDbInterface::disconnect();
  database::TemporaryDataInterface::disconnect();
  return 0;
}
