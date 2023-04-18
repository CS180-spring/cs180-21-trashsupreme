#ifndef __FILENODE_TEST_HPP_
#define __FILENODE_TEST_HPP_

#include "gtest/gtest.h"
#include "../../Objects/FileNode.hpp"

TEST(FileNode_Tests, Constructor_Filename_Assignment){
    char* fn = (char*)"Test.txt";
    FileNode* test = new FileNode(fn);
    EXPECT_EQ(test->get_Filename(),"Test.txt");
    }

#endif