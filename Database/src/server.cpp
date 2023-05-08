#include "../include/crow_all.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "../include/json.hpp"

using json = nlohmann::json;

std::vector<std::string> split(std::string s, std::string delimiter)
{
    int start = 0;
    int end;
    std::string token;
    std::vector<std::string> ret;

    while ((end = s.find(delimiter, start)) != std::string::npos)
    {
        token = s.substr(start, end - start);
        start = end + 1;
        ret.push_back(token);
    }

    ret.push_back(s.substr(start));
    return ret;
}

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
        // json j = json::parse(str);
        res.write(str);
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/query/<string>")
    ([](const crow::request &req, crow::response &res, std::string query)
     {
        std::ifstream file("/project/data/test.json");
        std::string str;

        std::vector<std::string> vec = split(query, "&");
        std::vector<std::string> temp;

        json j;
        for(int i = 0; i < vec.size(); i++) {
            temp = split(vec.at(i), "=");
            j[temp.at(0)] = temp.at(1);
        }
        

        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/update/<int>/<string>")
    ([](const crow::request &req, crow::response &res, int doc_id, std::string new_doc)
     {
        std::cout << "Updating document " << doc_id << " to " << new_doc << '\n';
        json j;
        j["response"] = "success";
        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/delete/<int>")
    ([](const crow::request &req, crow::response &res, int doc_id)
     {
        std::cout << "Deleting document " << doc_id << '\n';

        json j;
        j["response"] = "success";
        res.write(to_string(j));
        res.end(); });

    app.port(8080).multithreaded().run();

    return 0;
}