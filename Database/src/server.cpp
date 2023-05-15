#include "../include/crow_all.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>
#include <regex>
#include "../include/json.hpp"
#include "../Objects/FileTree.hpp"
#include "../Objects/FileNode.hpp"

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

void init_tree(FileTree *tree)
{
    using directory_iterator = std::filesystem::recursive_directory_iterator;
    std::string myPath = "/project/data";
    int id = 1;
    for (const auto &dirEntry : directory_iterator(myPath))
    {
        if (!std::filesystem::is_directory(dirEntry))
        {
            file::fileNode *file = new file::fileNode(dirEntry.path().string(), std::to_string(id));
            tree->filemap_add(file->get_docID(), file);
            std::cout << "file: " << file->get_filename() << " id: " << file->get_docID() << std::endl;
            id++;
        }
    }
}

int main()
{

    file::fileNode *file = new file::fileNode("root.txt", (char *)"0");

    FileTree *tree = new FileTree(file);
    tree->filemap_add(file->get_docID(), file);

    init_tree(tree);

    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors.global().allow_credentials().origin("http://localhost:5173");
    CROW_ROUTE(app, "/api/rest/v1/json/test")
    ([](const crow::request &req, crow::response &res)
     {
        json j;
        j["test"] = "/project/data/test.json";
        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/query/<string>")
    ([&](const crow::request &req, crow::response &res, std::string query)
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
        if (tree->find_key(std::regex_replace(temp.at(0), std::regex("%2F"), "/"))) {
            std::cout << "Found file " << temp.at(0) << std::endl;
            j[temp.at(0)] = "found";
        }

        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/add/<string>/<string>")
    ([&](const crow::request &req, crow::response &res, std::string doc_id, std::string query)
     {
        file::fileNode* new_file = new file::fileNode(query, doc_id);
        tree->filemap_add(new_file->get_docID(), new_file);
        std::ifstream file("/project/data/test.json");

        json j;
        j["response"] = "Success";
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

    CROW_ROUTE(app, "/api/rest/v1/json/delete/<string>")
    ([&](const crow::request &req, crow::response &res, std::string doc_id)
     {
        tree->filemap_remove(doc_id);
        std::cout << "Deleting document " << doc_id << '\n';

        json j;
        j["response"] = "success";
        res.write(to_string(j));
        res.end(); });

    app.port(8080).multithreaded().run();

    return 0;
}