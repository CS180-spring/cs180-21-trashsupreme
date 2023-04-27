#ifndef _ROOTTREE_H_
#define _ROOTTREE_H_

#include <vector>
#include <unordered_map>
#include <utility>
#include "TreeNode.hpp"
#include "FileTree.hpp"

class RootTree {
  public:
  //Constructor which creates the tree's root node.
  RootTree() {
    directory_name = (char*)"";
  }

    //Constructor which creates a node in the tree and passes in a directory name (will primarily not be used)
    RootTree(char* name) {
      directory_name = name;
    }

    ~RootTree() {
    }

    //Function which will add a FileTree to the RootTree object's directoryMap
    void map_add(char* directory, FileTree* child) {
      directoryMap.insert(std::make_pair(directory, child));
    }

    /*Helper function which outputs a message confirming whether a file tree of this
    file extension exists or not! */
    void find_key(char* key) {
      const auto& keys = directoryMap;
      if(keys.find(key) != keys.end()) {
        FileTree* mapData = keys.at(key);
        std::cout << "Node of file extension " << mapData->get_name() << " exists!" << std::endl;
      }
      else {
        std::cout << "Filetype of " << key << " extension has not been found!" << std::endl;
      }
    }

  private:
    char* directory_name;
    std::unordered_map<char*, FileTree*> directoryMap;
};


#endif