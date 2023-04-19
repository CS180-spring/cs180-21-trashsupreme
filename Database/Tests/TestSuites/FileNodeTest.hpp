#ifndef __FILENODE_TEST_HPP_
#define __FILENODE_TEST_HPP_

#include "gtest/gtest.h"
#include "../../Objects/FileNode.hpp"


TEST(FileNode_Tests, Constructor_Filename_Assignment){
    char* fn = (char*)"Test.txt";
    FileNode* testNode = new FileNode(fn);
    EXPECT_EQ(testNode->get_Filename(),fn);
    delete testNode;
    }

TEST(FileNode_Tests, Constructor_Timestamp_Assignment){
    char* fn = (char*)"Test.txt";
    time_t initialTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    FileNode* testNode = new FileNode(fn);
    time_t timeDiff = testNode->get_Timestamp() - initialTime;
    EXPECT_EQ(timeDiff,0);
    delete testNode;
    }

TEST(FileNode_Tests, UpdateFilename_Name_Updated){
    char* fn = (char*)"Test.txt";
    FileNode* testNode = new FileNode(fn);
    char* updatedName = (char*)"UpdatedName.txt";
    testNode->updateFilename(updatedName);
    EXPECT_EQ(testNode->get_Filename(),updatedName);
    delete testNode;
    }

TEST(FileNode_Tests, UpdateFilename_Timestamp_Updated){
    char* fn = (char*)"Test.txt";
    time_t initialTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    FileNode* testNode = new FileNode(fn);
    //Force time to pass before updating Node
    int cnt = 0;
    for(int i = 0; i<30000;i++){
        for(int j = 0; j<30000;j++){
            cnt++;
        }
        cnt=0;
    }
    testNode->updateFilename((char*)"Update");
    time_t stamp = testNode->get_Timestamp();
    time_t updatedTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    EXPECT_NE(stamp,initialTime);
    EXPECT_EQ(stamp,updatedTime);
    delete testNode;
    }

TEST(FileNode_Tests, Print_File){
    char* fn = (char*)"Test.txt";
    time_t initialTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    FileNode* testNode = new FileNode(fn);
    testing::internal::CaptureStdout();
    testNode->printFile();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "File Name: " + (std::string)fn + "\nDate Last Updated: " + (std::string)std::asctime(std::localtime(&initialTime)) + "\n";
    EXPECT_EQ(output, expected); 
}
#endif