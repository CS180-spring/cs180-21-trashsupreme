#ifndef __FILETREE_HPP__
#define __FILETREE_HPP__

#include "FileNode.hpp"
#include <vector>
#include <unordered_map>
#include <cstring>

class FileTree
{
public:
  /*Constructs a FileTree whose name is based on the filetype of the referenced FileNode
  Example: a file with filename "Words.txt" passed into the constructor will create a FileTree
  whose name is ".txt" */
  FileTree(file::fileNode *f)
  {
    name = f->get_fileExtension();
    filemap_add(f->get_docID(), f);
  }

  // Constructor which creates a folder with corresponding folder name and nodeID
  FileTree(std::string folderName, std::string ID)
  {
    name = folderName;
    nodeID = ID;
  }

  // Returns the name of the FileTree (ex: ".txt",".pdf", etc.)
  std::string get_name()
  {
    if(this == nullptr) {
      std::string x = "ERROR! Attempting to access folder which does not exist!\n";
      return x;
    }
    return this->name;
  }

  std::string get_nodeID() {
    if(this == nullptr) {
      std::string x = "ERROR! Attempting to access folder which does not exist!\n";
      return x;
    }
    return this->nodeID;
  }

  // Function which will add a file to the FileTree object's fileMap
  void filemap_add(std::string docID, file::fileNode *child)
  {
    fileMap.insert(std::make_pair(docID, child));
  }

  // Function which will add a folder to the FileTree object's folderMap
  void foldermap_add(std::string n_ID, FileTree *folder)
  {
    folderMap.insert(std::make_pair(n_ID, folder));
  }

  // Removes file with corresponding key (docID) from the tree
  void filemap_remove(std::string key)
  {

    file::fileNode* file;

    // If the current folder's folderMap & fileMap are empty (no folders to search through or files to search), then return
    if(this->folderMap.empty() == true && this->fileMap.empty() == true) {
      return;
    }
    // If there are no folders but there are files, iterate through the fileMap to search for the file to remove
    else if(this->folderMap.empty() == true && this->fileMap.empty() != true) {
      std::unordered_map<std::string, file::fileNode*>::iterator f_it = this->fileMap.begin();
      while(f_it != this->fileMap.end()) {
        if(f_it->second->get_docID() == key) {
          fileMap.erase(key);
          return; 
        }
        ++f_it;
      }
      return;
    }
    // If there are both folders & files, iterate through the fileMap first and then iterate through the folderMap using recursive function call
    else if(this->folderMap.empty() != true && this->fileMap.empty() != true) {
      std::unordered_map<std::string, file::fileNode*>::iterator f_it = this->fileMap.begin();
      std::unordered_map<std::string, FileTree*>::iterator it = this->folderMap.begin();
      while(f_it != this->fileMap.end()) {
        if(f_it->second->get_docID() == key) {
          fileMap.erase(key);
          return;
        }
        ++f_it;
      }
      while(it != this->folderMap.end()) {
        if(it->second->folderMap.empty() != true || it->second->fileMap.empty() != true) {
          it->second->filemap_remove(key);
        }
        ++it;
      }
      return;
    }
    //Otherwise, if there are no files but there are folders, search through the folders.
    else {
      std::unordered_map<std::string, FileTree*>::iterator it = this->folderMap.begin();
      while(it != this->folderMap.end()) {
        it->second->filemap_remove(key);
        ++it;
      }

      // If file to be removed doesn't exist within the path, return an error message.
      std::cout << "ERROR: File was not found in the path!" << std::endl;
      return;
    }
  }

  void foldermap_remove(std::string key) {
    // If the current folder's folderMap is empty (no folders to search through), then return
    if(this->folderMap.empty() == true) {
      return;
    }
    else {
      std::unordered_map<std::string, FileTree*>::iterator it = this->folderMap.begin();
      FileTree* folder;

      while(it != this->folderMap.end()) {
        // If the current FileTree's nodeID is equivalent to the key, clear its fileMap and folderMap
        if(it->second->get_nodeID() == key) {
          std::cout << "Folder has been found! Clearing its fileMap and folderMap..." << std::endl;
          it->second->clearMaps();
          this->folderMap.erase(key);
          return;
        }
        ++it; // Increment the iterator
      }
      it = this->folderMap.begin();
      while(it != this->folderMap.end()) {
        it->second->foldermap_remove(key);
        ++it;
      }
      return;
    }
  }

  // A helper function used in foldermap_remove to recursively clear all folderMaps and fileMaps under the located folder.
  void clearMaps() {

    // If this FileTree*'s fileMap is not empty, clear it.
    if(this->fileMap.empty() != true) {
      // Clear this folder's fileMap.
      this->fileMap.clear();
    }
    // If both maps are empty, return.
    if(this->fileMap.empty() && this->folderMap.empty() == true) {
      return;
    }
    // Otherwise, clear the folderMap recursively.
    if(this->folderMap.empty() != true) {
      std::unordered_map<std::string, FileTree*>::iterator folder_it = this->folderMap.begin();

      // Iterate through this folder's nested folders and make a recursive function call.
      while(folder_it != folderMap.end()) {
        // If the iterator FileTree's maps are both empty, do nothing and continue iterating.
        if(folder_it->second->folderMap.empty() == true && folder_it->second->fileMap.empty() == true) {  }
        // Else if the iterator FileTree's folderMap is empty, but not its fileMap, clear the fileMap.
        else if(folder_it->second->folderMap.empty() == true && folder_it->second->fileMap.empty() != true) {
          folder_it->second->clearMaps();
        }
        // Otherwise, make a recursive function call to clear all folders within this FileTree*
        else {
          folder_it->second->clearMaps();
        }
        ++folder_it;
      }
      return;
    }
  }

  /*Helper function which shall output a message confirming
  whether a file of this filename exists. */
  void doesFileExist(std::string key)
  {
    const auto &keys = fileMap; // auto which will search the fileMap
    if (keys.find(key) != keys.end())
    {
      file::fileNode *mapData = keys.at(key);
      std::cout << "File " << mapData->get_filename() << " exists!" << std::endl;
      return;
    }
    else
    {
      std::cout << "File " << key << " doesn't exist!" << std::endl;
      return;
    }
  }

  void outputFolders(FileTree *folder)
  {
    if (folder->folderMap.empty() == true)
    {
      std::unordered_map<std::string, file::fileNode *>::iterator it = folder->fileMap.begin();
      std::cout << "Files within folder \"" << folder->get_name() << "\": " << std::endl;
      while (it != folder->fileMap.end())
      {
        std::cout << "File: " << it->second->get_filename() << "\t \t \t"
                  << "docID: " << it->second->get_docID() << std::endl;
        it++;
      }
      std::cout << std::endl;
    }
    else
    {
      if (folder->fileMap.empty() != true)
      {
        std::unordered_map<std::string, file::fileNode *>::iterator it = folder->fileMap.begin();
        std::cout << "Files within folder \"" << folder->get_name() << "\": " << std::endl;
        while (it != folder->fileMap.end())
        {
          std::cout << "File: " << it->second->get_filename() << "\t \t \t"
                    << "docID: " << it->second->get_docID() << std::endl;
          it++;
        }
        std::cout << std::endl;
      }
      for (auto i = folder->folderMap.begin(); i != folder->folderMap.end(); i++)
      {
        std::cout << "Entering folder \"" << i->second->get_name() << "\" within folder \"" << folder->get_name() << "\"..." << std::endl;
        i->second->outputFolders(i->second);
      }
    }
  }

  /*Helper function which returns a boolean value confirming
  whether a file with this docID exists. */
  bool find_key(std::string key)
  {
    const auto &keys = fileMap; // auto which will search the fileMap
    if (keys.find(key) != keys.end())
    {
      // file::fileNode* mapData = keys.at(key);
      // std::cout << "File " << mapData->get_filename() << " exists!" << std::endl;
      return true;
    }
    else
    {
      // std::cout << "File " << key << " doesn't exist!" << std::endl;
      return false;
    }
  }

  file::fileNode *get_node(std::string key)
  {
    const auto &keys = fileMap;
    if (keys.find(key) != keys.end())
    {
      return keys.at(key);
    }
    else
    {
      return nullptr;
    }
  }
  bool find_folder(std::string key)
  {
    const auto &keys = folderMap; // auto which will search the folderMap
    if (keys.find(key) != keys.end())
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  file::fileNode* get_file(std::string key) {
    file::fileNode* file;

    // If the current folder's folderMap & fileMap are empty (no folders to search through or files to search), then return nullptr
    if(this->folderMap.empty() == true && this->fileMap.empty() == true) {
      return nullptr;
    }
    // If there are no folders but there are files, iterate through the fileMap to search for the file
    else if(this->folderMap.empty() == true && this->fileMap.empty() != true) {
      std::unordered_map<std::string, file::fileNode*>::iterator f_it = this->fileMap.begin();
      while(f_it != this->fileMap.end()) {
        if(f_it->second->get_docID() == key) {
          return f_it->second; 
        }
        ++f_it;
      }
      return nullptr;
    }
    // If there are both folders & files, iterate through the fileMap first and then iterate through the folderMap using recursive function call

    else if(this->folderMap.empty() != true && this->fileMap.empty() != true) {
      std::unordered_map<std::string, file::fileNode*>::iterator f_it = this->fileMap.begin();
      std::unordered_map<std::string, FileTree*>::iterator it = this->folderMap.begin();
      while(f_it != this->fileMap.end()) {
        if(f_it->second->get_docID() == key) {
          return f_it->second; 
        }
        ++f_it;
      }
      while(it != this->folderMap.end()) {
        if(it->second->folderMap.empty() != true || it->second->fileMap.empty() != true) {
          file = it->second->get_file(key);
          if(file == nullptr) { }
          else { return file; }
        }
        ++it;
      }
      return nullptr;
    }

    // Otherwise, if the fileMap is empty but there are folders, iterate through them using recursive function call

    else {
      std::unordered_map<std::string, FileTree*>::iterator it = this->folderMap.begin();
      while(it != this->folderMap.end()) {
        file = it->second->get_file(key);
        if(file == nullptr) { }
        else { return file; }
        ++it;
      }

      return nullptr;
    }
  }


  FileTree* get_folder(std::string key) {
    
    // If the current folder's folderMap is empty (no folders to search through), then return nullptr
    if(this->folderMap.empty() == true) {
      //std::cout << "No folders exist within the map of " << this->get_name() << "! Returning nullptr..." << std::endl;
      return nullptr;
    }

    // Otherwise, iterate through the folderMap, recursively calling this function on each folder whose map isn't empty

    else {
      std::unordered_map<std::string, FileTree*>::iterator it = this->folderMap.begin();
      FileTree* folder;

      while(it != this->folderMap.end()) {
        // If the current FileTree's nodeID is equivalent to the key, return the FileTree*
        if(it->second->get_nodeID() == key) { return it->second; }

        // Otherwise, make a recursive call of the function
        else {
          if(it->second->folderMap.empty() != true) {
            folder = it->second->get_folder(key);
            if(folder == nullptr) { }
            else {
              return folder;
            }
          }
        }
        ++it; // Increment the iterator
      }
      return nullptr; // Return nullptr if FileTree* with the specified key isn't found
    }
  }

  nlohmann::json get_json()
  {
    nlohmann::json ret;
    auto files = nlohmann::json::array();
    auto folders = nlohmann::json::array();
    for (auto i : fileMap)
    {
      files.push_back(i.second->get_json());
    }
    for (auto i : folderMap)
    {
      folders.push_back(i.second->get_json());
    }
    ret["Files"] = files;
    ret["Folders"] = folders;
    ret["Name"] = name;
    ret["NodeID"] = nodeID;
    return ret;
  }

  vector<file::fileNode *> search(std::string name, std::string ext)
  {
    vector<file::fileNode *> ret;
    vector<file::fileNode *> curr;
    vector<file::fileNode *> children;
    bool check_name = (name != "");
    bool check_ext = (ext != "");

    for (auto i: fileMap) {
      file::fileNode *curr_file = i.second;
      if (check_name && check_ext) {
        if (curr_file->get_stem() == name && curr_file->get_fileExtension() == ext) {
          children.push_back(curr_file);
        }
      } 
      else if (check_name) {
        if (curr_file->get_stem() == name) {
          children.push_back(curr_file);
        }
      }
      else if (check_ext) {
        if (curr_file->get_fileExtension() == ext) {
          children.push_back(curr_file);
        }
      }
    }

    for (auto i: folderMap) {
      vector<file::fileNode*> curr_folder = i.second->search(name, ext);

      curr.reserve(curr.size() + curr_folder.size());
      curr.insert(curr.end(), curr_folder.begin(), curr_folder.end());
    }

    ret.reserve(curr.size() + children.size());
    ret.insert(ret.end(), curr.begin(), curr.end());
    ret.insert(ret.end(), children.begin(), children.end());
    return ret;
  }

private:
  std::string name;
  std::string nodeID; // ID for a folder node
  std::unordered_map<std::string, file::fileNode *> fileMap;
  std::unordered_map<std::string, FileTree *> folderMap;
};
#endif
