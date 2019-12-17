#include "crow_all.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Lattice deployed";
    });

    app.port(8080).multithreaded().run();
}