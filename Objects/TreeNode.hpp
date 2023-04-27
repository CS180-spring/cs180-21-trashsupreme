#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <vector>
#include <cstring>
#include "FileNode.hpp"

class TreeNode {
  public:
  //Constructor which creates the tree's root node.
  TreeNode(FileNode* f) {
      file = f;
      filetype = (char*)"root";
    }

    //Constructor which creates a node in the tree and passes in a filetype (this node to be used as a child of a filetype node)
    TreeNode(FileNode* f, char* ft) {
      file = f;
      filetype = ft;
    }

    ~TreeNode() {
    }

    //Returns the file's filetype (ex: png, txt, pdf, etc.)
    char* get_Filetype() {
      return filetype;
    }

    void findFileTypeIndex(char* name) {
      char* output = NULL;
      char* period = (char*)".";
      output = strstr(name, output);
      if(output != NULL) { std::cout << "Substring found: " << output << std::endl; }
    }

    //Determines if a particular file's name and type already exists among the children of a filetype node.
    bool isDuplicateFile(TreeNode* directory, TreeNode* newFile) {
      for(int i = 0; i < directory->children.size(); ++i) {
        if(directory->children.at(i)->file->get_Filename() == newFile->file->get_Filename()) {
          return true;
        }
      }
      return false;
    }

    //A function which adds a child to a node's children vector
    void addChild(TreeNode* child) {
      if(isDuplicateFile(this, child) == true) {
        std::cout << "ERROR! File of this type and with this filename already exists! Please change filename." << std::endl;
      }
      else { this->children.push_back(child); }
      return;
    }

    /* Was working on a way to populate the root node with
    children nodes that represent each file type.
    A vector of TreeNode* with all supported file types must 
    be declared as a global variable somewhere.
    Must complete this some other time...*/
    void populateRoot(std::vector<TreeNode*> types) {
      if(this->get_Filetype() != "root") {
        std::cout << "ERROR! Cannot populate non-root node with children consisting of file types." << std::endl;
        return;
      }
      for(int i = 0; i < types.size(); i++) {
        //parent->addChild(parent, types.at(i));
        this->addChild(types.at(i));
      }
      return;
    }

    //Helper function which prints a nodes filetype
    void printFileType() {
      std::cout << "File type: " << filetype << std::endl;
      return;
    }

    //Helper function which returns all immediate children of a TreeNode
    void printChildren() {
      if(children.size() == 0) {
        std::cout << "ERROR! No children to display!" << std::endl;
        return;
      }

      std::cout << "File type: " << filetype << std::endl;
      for(int i = 0; i < children.size(); ++i) {
        std::cout << "Printing " << i+1 << "-th child's filename and file type..." << std::endl;
        std::cout << i+1 << "-th child's filename: " << children.at(i)->file->get_Filename() << std::endl;
        std::cout << i+1 << "-th child's filetype: " << children.at(i)->get_Filetype() << std::endl;
      }
      std::cout << std::endl;
    }

  private:
    FileNode* file;
    char* filetype;
    std::vector<TreeNode*> children;
};


#endif