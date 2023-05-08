#include <iostream>
#include "RootTree.hpp"

using namespace std;

int main() {
  RootTree* root = new RootTree();

  char* png = (char*)".png";
  char* txt = (char*)".txt";
  char* txt_filename = (char*)"Test.txt";
  char* png_filename = (char*)"Test.png";

  file::fileNode* txt_file = new file::fileNode(txt_filename, (char*)"1");
  FileTree* txt_node = new FileTree(txt_file);
  file::fileNode* png_file = new file::fileNode(png_filename, (char*)"2");
  FileTree* png_node = new FileTree(png_file);

  cout << txt_node->get_name() << endl;

  root->map_add(txt_node->get_name(), txt_node);
  root->map_add(png_node->get_name(), png_node);
  root->find_key(png_node->get_name());
  root->find_key(txt_node->get_name());

  return 0;
}