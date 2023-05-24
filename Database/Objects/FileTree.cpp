#include <iostream>
#include "FileTree.hpp"

using namespace std;
int main()
{

     std::string txt_filename1 = "Test.txt";
     std::string txt_filename2 = "Misc.txt";
     std::string txt_filename3 = "File.txt";
     std::string png_filename1 = "Test.png";
     std::string png_filename2 = "Image.png";
     std::string png_filename3 = "Picture.png";

     // File declarations for each folder
     file::fileNode *txt_file = new file::fileNode(txt_filename1, "1");
     file::fileNode *txt_file2 = new file::fileNode(txt_filename2, "2");
     file::fileNode *txt_file3 = new file::fileNode(txt_filename3, "3");
     file::fileNode *png_file = new file::fileNode(png_filename1, "4");
     file::fileNode *png_file2 = new file::fileNode(png_filename2, "5");
     file::fileNode *png_file3 = new file::fileNode(png_filename3, "6");
     file::fileNode *csv_misc_file = new file::fileNode("misc_file.csv", "7");
     file::fileNode *csv_data_file1 = new file::fileNode("datafile_1.csv", "8");
     file::fileNode *csv_data_file2 = new file::fileNode("datafile_2.csv", "9");
     file::fileNode *csv_help_file = new file::fileNode("help_file.csv", "10");
     file::fileNode *csv_videodata_file = new file::fileNode("csv_videodata.csv", "11");

     FileTree *txt_node = new FileTree(txt_file);
     FileTree *txt_folder1 = new FileTree("txt", "1");
     FileTree *png_folder1 = new FileTree("png", "2");
     FileTree *csv_root_folder = new FileTree("csv_root", "3");
     FileTree *csv_data_folder = new FileTree("csv_data", "4");
     FileTree *csv_videodata_folder = new FileTree("csv_videodata", "5");
     FileTree *file_folder = new FileTree("file_folder", "0");

     // fileNode 'txt_file' was added to FileTree txt_node's fileMap upon initialization.
     cout << "Adding .txt files to \"txt_folder\" fileMap..." << endl;
     txt_folder1->filemap_add(txt_file->get_docID(), txt_file);
     txt_folder1->filemap_add(txt_file2->get_docID(), txt_file2);
     txt_folder1->filemap_add(txt_file3->get_docID(), txt_file3);

     cout << "Adding .png files to \"png_folder\" fileMap..." << endl;
     png_folder1->filemap_add(png_file->get_docID(), png_file);
     png_folder1->filemap_add(png_file2->get_docID(), png_file2);
     png_folder1->filemap_add(png_file3->get_docID(), png_file3);

     cout << "Adding .csv files and folders to \"csv_root_folder\"..." << endl;
     csv_root_folder->filemap_add(csv_misc_file->get_docID(), csv_misc_file);
     csv_root_folder->filemap_add(csv_help_file->get_docID(), csv_help_file);
     csv_data_folder->filemap_add(csv_data_file1->get_docID(), csv_data_file1);
     csv_data_folder->filemap_add(csv_data_file2->get_docID(), csv_data_file2);
     csv_videodata_folder->filemap_add(csv_videodata_file->get_docID(), csv_videodata_file);
     csv_root_folder->foldermap_add(csv_data_folder->get_nodeID(), csv_data_folder);
     csv_data_folder->foldermap_add(csv_videodata_folder->get_nodeID(), csv_videodata_folder);

     std::string extension = txt_node->get_name();
     cout << "Testing file extension retrieval function..." << endl;
     cout << "File extension of filename (Test.txt) is: " << extension << endl
          << endl;

     cout << "Now searching for added file \"Test.txt\" in the map of folder \"txt\"..." << endl;
     cout << "Does file exist? (1 = YES, 0 = NO): " << txt_folder1->find_key(txt_file->get_docID()) << endl;
     txt_folder1->doesFileExist(txt_file->get_docID());
     cout << endl;

     cout << "Now searching for folder \"" << txt_folder1->get_name() << "\" within folder \"" << file_folder->get_name() << "\"..." << endl;
     file_folder->foldermap_add(txt_folder1->get_nodeID(), txt_folder1);
     file_folder->foldermap_add(png_folder1->get_nodeID(), png_folder1);
     file_folder->foldermap_add(csv_root_folder->get_nodeID(), csv_root_folder);
     cout << "Does folder exist? (1 = YES, 0 = NO): " << file_folder->find_folder(txt_folder1->get_nodeID()) << endl;
     cout << endl
          << "Now outputting all files/folders within \"file_folder\"..." << endl
          << endl;
     file_folder->outputFolders(file_folder);

     cout << endl
          << "Removing file \"Test.txt\" from folder \"txt\"..." << endl;
     txt_folder1->filemap_remove(txt_file->get_docID());
     cout << "Now searching for removed file in the fileMap..." << endl;
     cout << "Does file exist? (1 = YES, 0 = NO): " << txt_folder1->find_key(txt_file->get_docID()) << endl
          << endl;
     cout << "Printing files within folder to confirm removal of file..." << endl;
     txt_folder1->outputFolders(txt_folder1);

     cout << endl
          << "Testing get_folder function... " << endl;
     cout << "Searching for folder \"csv_data\" from root folder \"file_folder\"..." << endl;
     cout << "Returned folder pointer: " << file_folder->get_folder("4") << endl;
     cout << "Returned folder name: " << file_folder->get_folder("4")->get_name() << endl;

     cout << endl
          << "Now searching for folder \"csv_videos\", which is nested within \"csv_data\"..." << endl;
     cout << "Returned folder pointer: " << file_folder->get_folder("5") << endl;
     cout << "Returned folder name: " << file_folder->get_folder("5")->get_name() << endl;

     cout << endl
          << "Testing get_file function..." << endl;
     cout << "Searching for file \"csv_videodata.csv\" from root folder \"file_folder\"..." << endl;
     // file_folder->filemap_add("1", txt_file);
     cout << "Returned file pointer: " << file_folder->get_file("11") << endl;
     cout << "Returned file name: " << file_folder->get_file("11")->get_filename() << endl;

     cout << endl
          << "Now searching for file \"datafile1.csv\", which is nested within \"csv_data\"..." << endl;
     cout << "Returned file pointer: " << file_folder->get_file("8") << endl;
     cout << "Returned file name: " << file_folder->get_file("8")->get_filename() << endl;

     cout << endl
          << "Now searching for file \"Test.txt\", which no longer exists within this system..." << endl;
     cout << "Returned file pointer: " << file_folder->get_file("1") << endl;
     cout << "Returned file name: " << file_folder->get_file("1")->get_filename() << endl;

     return 0;

}