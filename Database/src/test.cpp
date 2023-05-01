#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/json.hpp"

using json = nlohmann::json;

int main()
{
    std::ifstream file("../data/test.json");
    std::string str;

    if (file)
    {
        std::ostringstream ss;
        ss << file.rdbuf();
        str = ss.str();
    }
    json j = json::parse(str);
    j["path"] = "test.json";
    std::cout << j["name"] << std::endl;
    std::cout << j["path"] << std::endl;
    json nested = j["groupmates"];
    std::cout << nested[0] << std::endl;

    return 0;
}