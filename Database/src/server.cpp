#include "../include/crow_all.h"
#include <iostream>

int main()
{

    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors.global().allow_credentials().origin("http://localhost:5173");
    CROW_ROUTE(app, "/api/rest/v1/test")
    ([]()
     {
        crow::json::wvalue x = {{"a", 1}, {"b", 2}};
        std::cout << "REQUESTED home route" << std::endl;
        return x; });

    app.port(18080).multithreaded().run();

    return 0;
}