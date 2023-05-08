#include "json.hpp"
#include "FileNode.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
#include <unordered_map>

using namespace std;
using json = nlohmann::json;

int main() {
  //Declare fileNodes using both constructor types for testing purposes
  file::fileNode f {(char*)"Test.txt", (char*)".txt", (char*)"1"};
  file::fileNode p { (char*)"Test.png", (char*)".png", (char*)"2" };
  file::fileNode* t = new file::fileNode((char*)"Test.pdf", (char*)"3");

  //Create an unordered map whose key value is a string (docID) and returns a JSON file
  std::unordered_map<std::string, json> fmap;

  //Declare JSON files which format our previously declared fileNodes
  json fn = f;
  json pn = p;
  json tn = *t;

  //Insert our first JSON file which was formatted through fileNode f.
  fmap.insert(std::make_pair(fn.at("docID"), fn));

  //Test if we can output the value at key: fileNode f's docID
  std::cout << fmap.at((char*)f.get_docID()) << std::endl;

  //Update fileNode f's filename.
  char* test = (char*)"Test_New.txt";
  f.updateFilename(test);

  /*Set JSON file fn to be equivalent to fileNode f again.
  TO DO: Create or modify a helper function which can update JSON file whenever fileNode is updated */
  fmap["1"] = f;

  //Insert new JSON to the unordered_map and output it
  fmap.insert(std::make_pair(pn.at("docID"), pn));
  std::cout << std::endl << fmap.at((char*)p.get_docID()) << std::endl;

  //Remove the newly added JSON file and insert new one with different docID "3". Then output the entire map to ensure proper removal and addition of JSONs to map
  fmap.erase("2");
  fmap.insert(std::make_pair(tn.at("docID"), tn));
  std::cout << std::endl << fmap << std::endl;

  return 0;
}