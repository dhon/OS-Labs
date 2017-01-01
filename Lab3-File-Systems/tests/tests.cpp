// tests.cpp
#include "../src/FileSystem.cpp"
#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

//Sample test cases:

//test create_file return code 1 for success
TEST(FSTest, create_file_test) {
	myFileSystem f ((char*) "disk0");
	int code = f.create_file((char*)"test.c",1);
	ASSERT_EQ(1,code);
}

//test delete_file return code -1 for failure
TEST(FSTest, delete_file_test) {
	myFileSystem f ((char*) "disk1");
	int code = f.delete_file((char*)"test.c");
	ASSERT_EQ(-1,code);
}

//TODO: add test cases here

// TEST(test_case_name, test_name) {
//  ... test body ...
// }

TEST(FSTest, create_file_test2) {
	myFileSystem f ((char*) "disk0");
	f.create_file((char*)"test1.c",8);
	f.create_file((char*)"test2.c",8);
	f.create_file((char*)"test3.c",8);
	f.create_file((char*)"test4.c",8);
	f.create_file((char*)"test5.c",8);
	f.create_file((char*)"test6.c",8);
	f.create_file((char*)"test7.c",8);
	f.create_file((char*)"test8.c",8);
	f.create_file((char*)"test9.c",8);
	f.create_file((char*)"test10",8);
	f.create_file((char*)"test11",8);
	f.create_file((char*)"test12",8);
	f.create_file((char*)"test13",8);
	f.create_file((char*)"test14",8);
	f.create_file((char*)"test15",8);
	f.create_file((char*)"test16",8);
	int code = f.create_file((char*)"test17",8);
	ASSERT_EQ(-1,code);
}

TEST(FSTest, delete_file_test2) {
	myFileSystem f ((char*) "disk1");
	f.create_file((char*)"test1.c",8);
	int code = f.delete_file((char*)"test1.c");
	ASSERT_EQ(1,code);
}

TEST(FSTest, ls_test) {
	myFileSystem f ((char*) "disk0");
	int code = f.create_file((char*)"hello",1);
	int test = f.ls();
	ASSERT_EQ(1,test);
}

TEST(FSTest, write_test) {
	myFileSystem f ((char*) "disk1");
	f.create_file((char*)"one",7);
	f.create_file((char*)"two",7);
	char* name = "two";
	int blockNum = 2;
	char buff[1024];
	int test = f.read(name, blockNum, buff);
	ASSERT_EQ(1,test);
}

TEST(FSTest, read_test) {
	myFileSystem f ((char*) "disk1");
	f.create_file((char*)"one",7);
	f.create_file((char*)"two",7);
	char* name = "two";
	char* name2 = "one";
	int blockNum = 1;
	int blockNum2 = 2;
	char buff[1024];
	int test = f.read(name, blockNum, buff);
	int test2 = f.read(name2, blockNum2, buff);
	ASSERT_EQ(1,test2);
	ASSERT_EQ(1,test);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}