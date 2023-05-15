#include <iostream>
#include "FileTree.hpp"

using namespace std;

int main() {

  char* png = (char*)".png";
  char* txt = (char*)".txt";
  char* txt_filename = (char*)"Test.txt";
  char* png_filename = (char*)"Test.png";
  file::fileNode* txt_file = new file::fileNode(txt_filename, (char*)"1");
  FileTree* txt_node = new FileTree(txt_file);

  char* extension = txt_node->get_name();
  cout << "File extension of filename (Test.txt) is: " << extension << endl << endl;

  cout << "Adding file Test.txt to fileMap..." << endl;
  txt_node->filemap_add(txt_file->get_docID(), txt_file);
  cout << "Now searching for added file in the map..." << endl;
  cout << txt_node->find_key(txt_filename) << endl;
  txt_node->doesFileExist(txt_file->get_docID());

  cout << endl << "Removing file Test.txt from the map..." << endl;
  txt_node->filemap_remove(txt_file->get_docID());
  cout << "Now searching for removed file in the fileMap..." << endl;
  txt_node->find_key(txt_file->get_docID());

  return 0;
}