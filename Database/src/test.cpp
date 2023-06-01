#include <filesystem>
#include <string>
#include <iostream>
#include <utility>
#include "../include/json.hpp"

using json = nlohmann::json;

int main()
{
    json j;
    j["Name"] = "frontend";
    j["Extension"] = "txt";
    j["Content"] = "hello\nworld";
    j["DocID"] = "5";

    json send_json;
    auto folders = json::array();
    auto json_array = json::array();
    send_json["Name"] = "root";
    json_array.push_back(j);
    send_json["Files"] = json_array;
    send_json["Folders"] = folders;
    auto send_array = json::array();
    send_array.push_back(send_json);

    std::cout << send_array.dump(2);
}