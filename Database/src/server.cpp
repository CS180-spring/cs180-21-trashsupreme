#include "../include/crow_all.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main()
{

    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors.global().allow_credentials().origin("http://localhost:5173");
    CROW_ROUTE(app, "/api/rest/v1/json/test")
    ([](const crow::request &req, crow::response &res)
     {
        std::ifstream file("/project/data/test.json");
        std::string str;

        if (file)
        {
            std::ostringstream ss;
            ss << file.rdbuf();
            str = ss.str();
        }
        // res.set_header("Content-Type", "application/json");
        res.write(str);
        res.end(); });

    app.port(8080).multithreaded().run();

    return 0;
}