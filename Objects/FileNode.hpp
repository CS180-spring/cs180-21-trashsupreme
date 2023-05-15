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

namespace file {
  class fileNode {
    public:
    //Test Constructor where all variables are declared by user
    fileNode(char* fn, char* type, char* ID) : filename(fn), filetype(type), docID(ID), timestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {}

    //Main constructor which creates filetype without explicitly declaring it
    fileNode(char* fn, char* ID) : filename(fn), filetype(strchr(filename, '.')), docID(ID), timestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {}
    ~fileNode() {}

    char* get_filename() {
      return filename;
    }

    char* get_fileExtension() {
      char* substr = this->filename;
      char* extension;
      extension = strchr(substr, '.');

      return extension;
    }

		char* get_docID() {
			return docID;
		}

    void updateFilename(char* fn) {
		  filename = fn;
      filename_string = (char*)filename;
		  timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	  }

    void printFile() {
		  std::cout << "File Name: " << filename
			<< "\nDate Last Updated: " << std::asctime(std::localtime(&timestamp)) << std::endl;
	  }

    char* filename;
    std::string filename_string = (char*)filename; //overloaded char* to string to be compatible with JSON functions below
    char* filetype;
    std::string filetype_string = (char*)filetype; //overloaded char* to string to be compatible with JSON functions below
    char* docID;
    std::string docID_string = (char*)docID; //overloaded char* to string to be compatible with JSON functions below
		char* path;
		std::string path_string = (char*)path;
    std::time_t timestamp;
  };
    void to_json(json& j, const fileNode& p) {
        j = json{ {"filename", p.filename}, {"filetype", p.filetype}, {"docID", p.docID}, {"timestamp", p.timestamp} };
    }

    void from_json(const json& j, fileNode& p) {
        j.at("filename").get_to(p.filename_string);
        j.at("filetype").get_to(p.filetype_string);
        j.at("docID").get_to(p.docID_string);
        j.at("timestamp").get_to(p.timestamp);
    }
}

#endif