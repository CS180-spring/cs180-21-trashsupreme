#ifndef _FILENODE_H_
#define _FILENODE_H_

#include "json.hpp"
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
    fileNode(std::string fn, std::string ID) : filename(fn), filetype(filename.substr(filename.find(".") + 1)), docID(ID), timestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {}
    ~fileNode() {}

    std::string get_filename()
    {
      return filename;
    }

    std::string get_fileExtension()
    {
      std::string substring = this->filename;
      std::string extension;
      // extension = strchr(substr, '.');
      extension = substring.substr(substring.find(".") + 1);

      return extension;
    }

    std::string get_docID()
    {
      return docID;
    }

    void updateFilename(std::string fn)
    {
      filename = fn;
      // filename_string = (std::string)filename;
      timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }

    void printFile()
    {
      std::cout << "File Name: " << filename
                << "\nDate Last Updated: " << std::asctime(std::localtime(&timestamp)) << std::endl;
    }

    std::string filename;
    // std::string filename_string = (std::string)filename; // overloaded char* to string to be compatible with JSON functions below
    std::string filetype;
    // std::string filetype_string = (std::string)filetype; // overloaded char* to string to be compatible with JSON functions below
    std::string docID;
    // std::string docID_string = (std::string)docID; // overloaded char* to string to be compatible with JSON functions below
    std::string path;
    // std::string path_string = (std::string)path;
    std::time_t timestamp;
  };
  void to_json(json &j, const fileNode &p)
  {
    j = json{{"filename", p.filename}, {"filetype", p.filetype}, {"docID", p.docID}, {"timestamp", p.timestamp}};
  }

  void from_json(const json &j, fileNode &p)
  {
    j.at("filename").get_to(p.filename);
    j.at("filetype").get_to(p.filetype);
    j.at("docID").get_to(p.docID);
    j.at("timestamp").get_to(p.timestamp);
  }
}

#endif