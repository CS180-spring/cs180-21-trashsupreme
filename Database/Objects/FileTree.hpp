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
    std::string result = "\n";
    return this->name;
  }

  std::string get_nodeID()
  {
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
    // If a file with this key exists, then we can properly remove it
    if (this->find_key(key) != false)
    {
      fileMap.erase(key);
      return;
    }
    // Otherwise, we cannot remove a file with a key that is not mapped/does not exist!
    else
    {
      std::cout << "Unable to remove as a file with that key doesn't exist!" << std::endl;
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
  }

  FileTree *get_folder(std::string key)
  {
    const auto &keys = folderMap;
    if (keys.find(key) != keys.end())
    {
      return keys.at(key);
    }
    else
    {
      return nullptr;
    }
  }

private:
  std::string name;
  std::string nodeID; // ID for a folder node
  std::unordered_map<std::string, file::fileNode *> fileMap;
  std::unordered_map<std::string, FileTree *> folderMap;
};
#endif
