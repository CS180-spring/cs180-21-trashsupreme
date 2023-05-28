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
std::string read_file(std::string path)
{
    std::ifstream ifs(path);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

FileTree *init_tree()
{
    int folder_index = 1;
    int file_index = 0;
    // std::string myPath = "../data";
    std::string myPath = "/project/data";
    FileTree *root = new FileTree("root", myPath);
    using directory_iterator = std::filesystem::recursive_directory_iterator;
    int id = 0;
    for (const auto &dirEntry : directory_iterator(myPath))
    {
        std::cout << dirEntry << std::endl;
        if (std::filesystem::is_directory(dirEntry))
        {
            std::cout << "directory: " << dirEntry << std::endl;
            if (dirEntry.path().parent_path() == myPath)
            {
                std::cout << dirEntry << " is in the root directory" << std::endl;
                FileTree *new_tree = new FileTree(dirEntry.path().stem(), dirEntry.path());
                root->foldermap_add(new_tree->get_nodeID(), new_tree);
            }
            else
            {
                std::cout << dirEntry << " is not in the root directory" << std::endl;
                FileTree *new_tree = new FileTree(dirEntry.path().stem(), dirEntry.path());
                root->get_folder(dirEntry.path().parent_path())->foldermap_add(new_tree->get_nodeID(), new_tree);
            }
        }
        else
        {
            file::fileNode *file = new file::fileNode(dirEntry.path().filename(), std::to_string(id++));
            file->set_path(dirEntry.path());
            if (dirEntry.path().parent_path() == myPath)
            {
                root->filemap_add(file->get_docID(), file);
            }
            else
            {
                root->get_folder(dirEntry.path().parent_path())->filemap_add(file->get_docID(), file);
            }
        }
    }
    return root;
}

int main()
{

    FileTree *tree = init_tree();

    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors.global().allow_credentials().origin("http://localhost:5173");
    CROW_ROUTE(app, "/api/rest/v1/json/test")
    ([](const crow::request &req, crow::response &res)
     {
        using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
        std::string myPath = "/project/data";
        // std::string myPath = "../data";
        int id = 0;
        for (const auto &dirEntry : recursive_directory_iterator(myPath))
        {
            // std::cout << dirEntry.path().string() << std::endl;
            std::cout << dirEntry << std::endl;
            id++;
        }
        json j;
        j["response"] = "OK";
        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/query/<string>")
    ([&](const crow::request &req, crow::response &res, std::string query)
     {
        std::cout << "Query: " << query << std::endl;
        std::string str;
        auto send_array = json::array();
        // send_array.push_back(tree->get_file(query)->get_json());
        // send_array.push_back(tree->get_file("0")->get_json());
        send_array.push_back(tree->get_json());
        res.write(to_string(send_array));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/create/<string>/<string>")
    ([&](const crow::request &req, crow::response &res, std::string doc_id, std::string query)
     {
        file::fileNode* new_file = new file::fileNode(query, doc_id);
        tree->filemap_add(new_file->get_docID(), new_file);

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

    CROW_ROUTE(app, "/api/rest/v1/json/delete/file/<string>")
    ([&](const crow::request &req, crow::response &res, std::string doc_id)
     {
        // tree->filemap_remove(doc_id);
        std::cout << "Still under construction: delete file" << std::endl;

        json j;
        j["response"] = "success";
        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/delete/folder/<string>")
    ([&](const crow::request &req, crow::response &res, std::string doc_id)
     {
        // tree->filemap_remove(doc_id);
        std::cout << "Still under construction: delete folder" << std::endl;

        json j;
        j["response"] = "success";
        res.write(to_string(j));
        res.end(); });

    app.port(8080).multithreaded().run();

    return 0;
}