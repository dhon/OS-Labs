// tests.cpp
#include "../src/BoundedBuffer.cpp"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

//Test checking if bounded buffer is empty
TEST(PCTest, Test1) { 
    BoundedBuffer *BB = new BoundedBuffer(5);
    EXPECT_TRUE(BB->isEmpty());
    
    delete BB;
}

//Test checking append() and remove() from buffer 
TEST(PCTest, Test2){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(0);
    ASSERT_EQ(0,BB->remove());

    delete BB;
}

//TODO: add test cases here

// Append Remove Test 1.
TEST(PCTest, Test3){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(7);
    ASSERT_EQ(7,BB->remove());
    delete BB;
}

// Append Remove Test 2.
TEST(PCTest, Test4){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(7);
    BB->append(4);
    BB->append(1);
    BB->remove();
    BB->remove();
    ASSERT_EQ(1,BB->remove());
    delete BB;
}

// Append Remove Test 3.
TEST(PCTest, Test5){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(1);
    BB->append(2);
    BB->append(3);
    BB->remove();
    BB->remove();
    BB->append(4);
    BB->remove();
    BB->append(5);
    BB->append(6);
    BB->append(7);
    BB->append(8);
    BB->remove();
    BB->append(9);
    ASSERT_EQ(5,BB->remove());
    delete BB;
}

// isEmpty() on new
TEST(PCTest, Test6){
    BoundedBuffer *BB = new BoundedBuffer(5);
    ASSERT_EQ(true,BB->isEmpty());
    delete BB;
}

// isEmpty() expect false
TEST(PCTest, Test7){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(5);
    ASSERT_EQ(false,BB->isEmpty());
    delete BB;
}

// isEmpty() after remove
TEST(PCTest, Test8){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(5);
    BB->remove();
    ASSERT_EQ(true,BB->isEmpty());
    delete BB;
}

// isFull() expect true
TEST(PCTest, Test9){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(1);
    BB->append(2);
    BB->append(3);
    BB->append(4);
    BB->append(5);
    ASSERT_EQ(true,BB->isFull());
    delete BB;
}

// isFull() expect false
TEST(PCTest, Test10){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(0);
    ASSERT_EQ(false,BB->isFull());
    delete BB;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
