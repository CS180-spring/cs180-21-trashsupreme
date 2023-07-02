#ifndef __TREENODE_TEST_HPP__
#define __TREENODE_TEST_HPP__

#include "gtest/gtest.h"
#include "../Objects/TreeNode.hpp"

TEST(TreeNode_Tests, Constructor_Root_Assignment) {
  char* fn = (char*)"root";
  FileNode* rootNode = new FileNode(fn);
  TreeNode* root = new TreeNode(rootNode);
  EXPECT_EQ(rootNode->get_Filename(), fn);
  delete rootNode;
  delete root;
}

TEST(TreeNode_Tests, Constructor_Filetype_Assignment) {
  char* fn = (char*)"Test.png";
  char* ft = (char*)"png";
  FileNode* pngFile = new FileNode(fn);
  TreeNode* png = new TreeNode(pngFile);
  EXPECT_EQ(png->get_Filetype(), ft);
  delete pngFile;
  delete png;
}

TEST(TreeNode_Tests, Return_Filetype) {
  char* fn = (char*)"Test.txt";
  char* ft = (char*)"txt";
  FileNode* txtFile = new FileNode(fn);
  TreeNode* txt = new TreeNode(txtFile);
  EXPECT_EQ(txt->get_Filetype(), ft);
  delete txtFile;
  delete txt;
}

TEST(TreeNode_Tests, Duplicate_File_IsTrue) {
  char* fn = (char*)"txt";
  char* ft = (char*)"txt";
  FileNode* txt_directory = new FileNode(fn);
  TreeNode* txt_treeDirectory = new TreeNode(txt_directory);

  char* fn2 = (char*)"Test.txt";
  char* ft2 = (char*)"txt";
  FileNode* txt_file = new FileNode(fn);
  TreeNode* txt_fileNode = new TreeNode(txt_file);
  txt_treeDirectory->addChild(txt_fileNode);

  char* fn3 = (char*)"Test.txt";
  char* ft3 = (char*)"txt";
  FileNode* txt_fileDuplicate = new FileNode(fn);
  TreeNode* txt_fileNodeDuplicate = new TreeNode(txt_fileDuplicate);
  txt_treeDirectory->addChild(txt_fileNodeDuplicate);

  EXPECT_TRUE(txt_treeDirectory->isDuplicateFile(txt_treeDirectory, txt_fileNodeDuplicate));
  delete txt_directory;
  delete txt_treeDirectory;
  delete txt_file;
  delete txt_fileNode;
  delete txt_fileDuplicate;
  delete txt_fileNodeDuplicate;
}

TEST(TreeNode_Tests, Duplicate_File_IsFalse) {
  char* fn = (char*)"txt";
  char* ft = (char*)"txt";
  FileNode* txt_directory = new FileNode(fn);
  TreeNode* txt_treeDirectory = new TreeNode(txt_directory);

  char* fn2 = (char*)"Test.txt";
  char* ft2 = (char*)"txt";
  FileNode* txt_file = new FileNode(fn);
  TreeNode* txt_fileNode = new TreeNode(txt_file);
  txt_treeDirectory->addChild(txt_fileNode);

  char* fn3 = (char*)"Test.png";
  char* ft3 = (char*)"png";
  FileNode* png_file = new FileNode(fn);
  TreeNode* png_fileNode = new TreeNode(png_file);
  txt_treeDirectory->addChild(png_fileNode);

  EXPECT_FALSE(txt_treeDirectory->isDuplicateFile(txt_treeDirectory, png_fileNode));
  delete txt_directory;
  delete txt_treeDirectory;
  delete txt_file;
  delete txt_fileNode;
  delete png_file;
  delete png_fileNode;
}

#endif