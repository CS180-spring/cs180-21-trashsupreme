#ifndef _FILENODE_H_
#define _FILENODE_H_

#include "json.hpp"
#include <fstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cassert>
#include <unordered_map>

using namespace std;
using json = nlohmann::json;

namespace file
{
  class fileNode
  {
  public:
    // Test Constructor where all variables are declared by user
    fileNode(std::string fn, std::string type, std::string ID) : filename(fn), filetype(type), docID(ID), timestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {}

    // Main constructor which creates filetype without explicitly declaring it
    fileNode(std::string fn, std::string ID) : filename(fn), filetype(filename.substr(filename.find("."))), docID(ID), timestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {}
    ~fileNode() {}

    std::string get_filename()
    {
      if(this == nullptr) { 
        return "Invalid! File doesn't exist!\n";
      }
      return filename;
    }

    std::string get_fileExtension()
    {
      if(this == nullptr) { 
        return "Invalid! File doesn't exist!\n";
      }
      std::string substring = this->filename;
      std::string extension;
      extension = substring.substr(substring.find("."));

      return extension;
    }

    std::string get_docID()
    {
      if(this == nullptr) { 
        return "Invalid! File doesn't exist!\n";
      }
      return docID;
    }

    void updateFilename(std::string fn)
    {
      filename = fn;
      timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }

    void printFile()
    {
      std::cout << "File Name: " << filename
                << "\nDate Last Updated: " << std::asctime(std::localtime(&timestamp)) << std::endl;
    }

    // NLOHMANN_DEFINE_TYPE_INTRUSIVE(filename, filetype, docID, path, timestamp);

    friend void to_json(nlohmann::json &nlohmann_json_j, const fileNode &nlohmann_json_t)
    {
      nlohmann_json_j["filename"] = nlohmann_json_t.filename;
      nlohmann_json_j["filetype"] = nlohmann_json_t.filetype;
      nlohmann_json_j["docID"] = nlohmann_json_t.docID;
      nlohmann_json_j["path"] = nlohmann_json_t.path;
      nlohmann_json_j["content"] = nlohmann_json_t.content;
      nlohmann_json_j["timestamp"] = nlohmann_json_t.timestamp;
    }

    friend void from_json(const nlohmann::json &nlohmann_json_j, fileNode &nlohmann_json_t)
    {
      nlohmann_json_t.filename = nlohmann_json_j.at("filename");
      nlohmann_json_t.filetype = nlohmann_json_j.at("filetype");
      nlohmann_json_t.docID = nlohmann_json_j.at("docID");
      nlohmann_json_t.path = nlohmann_json_j.at("path");
      nlohmann_json_t.content = nlohmann_json_j.at("content");
      nlohmann_json_t.timestamp = nlohmann_json_j.at("timestamp");
    }

    std::string read_file()
    {
      std::ifstream ifs(path);
      std::string content((std::istreambuf_iterator<char>(ifs)),
                          (std::istreambuf_iterator<char>()));
      return content;
    }

    nlohmann::json get_json()
    {
      nlohmann::json ret;

      ret["Name"] = get_filename();
      ret["Extension"] = get_fileExtension();
      ret["DocID"] = docID;
      ret["Content"] = read_file();
      return ret;
    }

    void set_path(std::string new_path) {
      path = new_path;
    }

    std::string get_path() {
      return path;
    }

  private:
    std::string filename;
    std::string filetype;
    std::string docID;
    std::string path;
    std::string content;
    std::time_t timestamp;
  };

  /*void to_json(json &j, const fileNode &p)
  {
    j = json{{"filename", p.filename}, {"filetype", p.filetype}, {"docID", p.docID}, {"timestamp", p.timestamp}};
  }

  void from_json(const json &j, fileNode &p)
  {
    j.at("filename").get_to(p.filename);
    j.at("filetype").get_to(p.filetype);
    j.at("docID").get_to(p.docID);
    j.at("timestamp").get_to(p.timestamp);
  }*/
}

#endif