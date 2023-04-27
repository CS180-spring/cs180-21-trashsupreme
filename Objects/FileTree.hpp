#ifndef __FILETREE_HPP__
#define __FILETREE_HPP__

#include "FileNode.hpp"
#include <vector>
#include <unordered_map>
#include <cstring>

class FileTree {
  public:
    /*Constructs a FileTree whose name is based on the filetype of the referenced FileNode 
    Example: a file with filename "Words.txt" passed into the constructor will create a FileTree
    whose name is ".txt" */
    FileTree(FileNode* f) {
      name = f->get_fileExtension();
    }

    //Returns the name of the FileTree (ex: ".txt",".pdf", etc.)
    char* get_name() {
      char* result = (char*)"\n";
      return this->name;
    }

    //Function which will add a file to the FileTree object's fileMap
    void filemap_add(char* filename, FileNode* child) {
      fileMap.insert(std::make_pair(filename, child));
    }

    void filemap_remove(char* key) {
      fileMap.erase(key);
    }

    /*Helper function which shall output a message confirming
    whether a file of this filename exists. */
    void find_key(char* key) {
      const auto& keys = fileMap; //auto which will search the fileMap
      if(keys.find(key) != keys.end()) {
        FileNode* mapData = keys.at(key);
        std::cout << "File " << mapData->get_Filename() << " exists!" << std::endl;
      }
      else {
        std::cout << "File " << key << " doesn't exist!" << std::endl;
      }
    }

  private:
    char* name;
    std::unordered_map<char*, FileNode*> fileMap;
};

#endif 