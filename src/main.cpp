// std lib
#include <string>
#include <memory>

// lib
#include "crow_all.h"

// modules

int main()
{

    std::string api_output;    
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Lattice deployed";
    });

    CROW_ROUTE(app, "/add").methods("PUT"_method)([&](const crow::request &req){
      return api_output.c_str();
    });
    CROW_ROUTE(app, "/devices").methods("GET"_method)([&](const crow::request &req){
      return api_output.c_str();
    });


    app.port(8080).multithreaded().run();
}
