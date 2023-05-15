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
    FileTree(file::fileNode* f) {
      name = f->get_fileExtension();
    }

    //Constructor which creates a folder with corresponding folder name and nodeID
    FileTree(char* folderName, char* ID) {
      name = folderName;
      nodeID = ID;
    }

    //Returns the name of the FileTree (ex: ".txt",".pdf", etc.)
    char* get_name() {
      char* result = (char*)"\n";
      return this->name;
    }

    //Function which will add a file to the FileTree object's fileMap
    void filemap_add(char* docID, file::fileNode* child) {
      fileMap.insert(std::make_pair(docID, child));
    }

    //Function which will add a folder to the FileTree object's folderMap
    void filemap_add(char* n_ID, FileTree* folder) {
      folderMap.insert(std::make_pair(n_ID, folder));
    }

    //Removes file with corresponding key (docID) from the tree
    void filemap_remove(char* key) {
      //If a file with this key exists, then we can properly remove it
      if(this->find_key(key) != false) {
        fileMap.erase(key);
        return;
      }
      //Otherwise, we cannot remove a file with a key that is not mapped/does not exist!
      else {
        std::cout << "Unable to remove as a file with that key doesn't exist!" << std::endl;
        return;
      }
    }

    /*Helper function which shall output a message confirming
    whether a file of this filename exists. */
    void doesFileExist(char* key) {
      const auto& keys = fileMap; //auto which will search the fileMap
      if(keys.find(key) != keys.end()) {
        file::fileNode* mapData = keys.at(key);
        std::cout << "File " << mapData->get_filename() << " exists!" << std::endl;
        return;
      }
      else {
        std::cout << "File " << key << " doesn't exist!" << std::endl;
        return;
      }
    }

    /*Helper function which returns a boolean value confirming
    whether a file with this docID exists. */
    bool find_key(char* key) {
      const auto& keys = fileMap; //auto which will search the fileMap
      if(keys.find(key) != keys.end()) {
        //file::fileNode* mapData = keys.at(key);
        //std::cout << "File " << mapData->get_filename() << " exists!" << std::endl;
        return true;
      }
      else {
        //std::cout << "File " << key << " doesn't exist!" << std::endl;
        return false;
      }
    }

  private:
    char* name;
    char* nodeID; //ID for a folder node
    std::unordered_map<char*, file::fileNode*> fileMap;
    std::unordered_map<char*, FileTree*> folderMap;
};

#endif 