// std lib
#include <string>
#include <memory>

// lib
#include "crow_all.h"

// proto
#include "thing_buffer.pb.h"

// modules
// #include "device/device_manager.h"

int main()
{

    std::string api_output;    
    crow::SimpleApp app;
    // std::shared_ptr<device::DeviceManager> device_manager = \
      std::make_shared<device::DeviceManager>();

    CROW_ROUTE(app, "/")([](){
        return "Lattice deployed";
    });

    CROW_ROUTE(app, "/add").methods("PUT"_method)([&](const crow::request &req){
      // device_manager->Add(api_output);
      return api_output.c_str();
    });
    CROW_ROUTE(app, "/devices").methods("GET"_method)([&](const crow::request &req){
      // device_manager->GetDevices(api_output);
      return api_output.c_str();
    });


    app.port(8080).multithreaded().run();
}
