// std lib
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

// boost imports
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

// lib
#include "crow_all.h"

// proto
#include "thing_buffer.pb.h"
#include "user.pb.h"

using namespace std;
using namespace boost::uuids;

void demo_user() {
  shared_ptr<lattice_hub::user::User> user1 = make_shared<lattice_hub::user::User>();
  // Generate random boost uuid, convert it to string-16 bytes and store.
  user1->set_id(boost::lexical_cast<string>(random_generator()()).c_str());
  user1->set_name("Lattic_hub_dummy_user");
  // Set current time as registered time.
  user1->set_registered_time(time(NULL));
  cout << user1->DebugString() << endl;
}

int main()
{

    std::string api_output;    
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Lattice deployed";
    });
    demo_user();

    CROW_ROUTE(app, "/add").methods("PUT"_method)([&](const crow::request &req){
      return api_output.c_str();
    });
    CROW_ROUTE(app, "/devices").methods("GET"_method)([&](const crow::request &req){
      return api_output.c_str();
    });


    app.port(8080).multithreaded().run();
}
