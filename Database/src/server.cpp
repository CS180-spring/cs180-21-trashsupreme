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
#include "../include/encode.h"
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
    // std::string myPath = "/project/data";
    std::string myPath = "/usr/share/data";
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
    CROW_ROUTE(app, "/api/rest/v1/json/test/filesystem")
    ([](const crow::request &req, crow::response &res)
     {
        using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
        std::string myPath = "/usr/share/data";
        std::string ret = "";
        for (const auto &dirEntry : recursive_directory_iterator(myPath))
        {
            std::cout << dirEntry << std::endl;
            ret += dirEntry.path().string() + '\n';
        }
        res.write(ret);
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/test/tree")
    ([&](const crow::request &req, crow::response &res)
     {
        res.write(tree->get_json().dump(4));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/query")
    ([&](const crow::request &req, crow::response &res)
     {
        std::string str;
        auto send_array = json::array();
        // send_array.push_back(tree->get_file(query)->get_json());
        // send_array.push_back(tree->get_file("0")->get_json());
        send_array.push_back(tree->get_json());
        res.write(to_string(send_array));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/query/<string>")
    ([&](const crow::request &req, crow::response &res, std::string query)
     {
        std::cout << "Query: " << query << std::endl;
        query = decodeURIComponent(query);
        vector<std::string> items = split(query, "&");
        std::string name = "";
        std::string ext = "";
        FileTree temp_tree("search", "-1");
        for(auto i: items) {
            vector<std::string> split_items = split(i, "=");
            if (split_items.at(0) == "name") {
                name = split_items.at(1);
            }
            else if (split_items.at(0) == "extension") {
                ext = split_items.at(1);
            }
        }
        auto send_array = json::array();
        // send_array.push_back(tree->get_json());
        vector<file::fileNode*> results = tree->search(name, ext);
        for (auto i: results) {
            // send_array.push_back(i->get_json());
            temp_tree.filemap_add(i->get_docID(), i);
        }
        send_array.push_back(temp_tree.get_json());
        res.write(to_string(send_array));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/create/file/<string>/<string>/<string>")
    ([&](const crow::request &req, crow::response &res, std::string file_name, std::string node_id, std::string content)
     {
        std::string path = decodeURIComponent(node_id);
        std::string new_content = decodeURIComponent(content);
        std::cout << new_content << std::endl;
        std::ofstream new_file(path + "/" + file_name);
        new_file << new_content;
        new_file.close();
        json j;
        j["message"] = "Success";
        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/create/folder/<string>/<string>/<string>")
    ([&](const crow::request &req, crow::response &res, std::string node_id, std::string parent_id, std::string folder_name)
     {
        std::string path = decodeURIComponent(node_id);
        std::string parent_path = decodeURIComponent(parent_id);
        std::string name = decodeURIComponent(folder_name);

        std::cout << "new child path: " << path << std::endl; 
        std::cout << "parent path: " << parent_path << std::endl;

        FileTree* parent_node = tree->get_folder(parent_path);

        json j;
        if (parent_node != nullptr && tree->get_folder(path) == nullptr) {
            bool success = std::filesystem::create_directory(path);
            if (success)
            { 
                FileTree* new_node = new FileTree(name, path);
                parent_node->foldermap_add(new_node->get_nodeID(), new_node);
                j["message"] = "Success";
            }
            else {
                j["message"] = "Failure";
            }
        }
        else {
            j["message"] = "Failure";
        }

        res.write(to_string(j)),
        res.end(); });

    // CROW_ROUTE(app, "/api/rest/v1/json/update/<int>/<string>")
    CROW_ROUTE(app, "/api/rest/v1/json/update/<string>/<string>")
    // ([&](const crow::request &req, crow::response &res, int doc_int, std::string new_content)
    ([&](const crow::request &req, crow::response &res, std::string doc_id, std::string new_content)
     {
        // std::string doc_id = std::to_string(doc_int);
        file::fileNode *file = tree->get_file(doc_id);
        json j;
        if (file != nullptr)
        {
            std::string path = file->get_path();
            std::cout << "before escapes: " << new_content << std::endl;
            new_content = decodeURIComponent(new_content);
            std::cout << "after escapes: " << new_content << std::endl;
            std::ofstream new_file(path);
            new_file << new_content;
            new_file.close();

            j["response"] = "success";
        }
        else
        {
            j["response"] = "fail";
        }
        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/delete/file/<string>")
    ([&](const crow::request &req, crow::response &res, std::string doc_id)
     {
        // tree->filemap_remove(doc_id);
        std::cout << "Still under construction: delete file" << std::endl;
        file::fileNode *file_to_delete = tree->get_file(doc_id);
        bool success = false;
        json j;
        if (file_to_delete)
        {
            std::cout << "Deleting file " << file_to_delete->get_path() << std::endl;
            success = std::filesystem::remove(file_to_delete->get_path());
            if (success)
            {
                tree->filemap_remove(doc_id);
                std::cout << "Successfully deleted " << file_to_delete->get_path() << std::endl;
                j["response"] = "success";
            }
            else
            {
                std::cout << "Failed to delete " << file_to_delete->get_path() << std::endl;
                j["response"] = "failure";
            }
        }
        else
        {
            j["response"] = "failure";
        }

        res.write(to_string(j));
        res.end(); });

    CROW_ROUTE(app, "/api/rest/v1/json/delete/folder/<string>")
    ([&](const crow::request &req, crow::response &res, std::string node_id)
     {
        std::string folder_path = decodeURIComponent(node_id);
        FileTree *folder_to_delete = tree->get_folder(folder_path);
        bool success = false;
        if (folder_to_delete)
        {
            std::cout << "Deleting folder " << folder_to_delete->get_nodeID() << std::endl;
            success = std::filesystem::remove_all(std::filesystem::path(folder_path));
            if (success)
            {
                tree->foldermap_remove(folder_path);
                std::cout << "Successfully deleted " << folder_path << std::endl;
            }
            else
            {
                std::cout << "Failed to delete " << folder_path << std::endl;
            }
        }
        else
        {
            std::cout << "Folder " << folder_path << " does not exist!" << std::endl;
        }

        json j;
        j["response"] = "success";
        res.write(to_string(j));
        res.end(); });

    app.port(8080).multithreaded().run();

    return 0;
}