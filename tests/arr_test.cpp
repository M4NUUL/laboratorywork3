#include "gtest/gtest.h"
#include "../arr.h"
#include "../serialize.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

using namespace std;

class OutputCapture {
    std::stringstream buffer;
    std::streambuf* prev;
public:
    OutputCapture() : prev(std::cout.rdbuf(buffer.rdbuf())) {}
    ~OutputCapture() { std::cout.rdbuf(prev); }
    std::string str() { return buffer.str(); }
};

TEST(MyArrTest, Branch_CapacityAndShrink) {
    MyArr arr;

    for(int i=0; i<65; ++i) {
        arr.addEnd("x");
    }
    EXPECT_GE(arr.lenArr(), 65);
    
    int startSize = arr.lenArr();
    for(int i=0; i < startSize; ++i) {
        arr.delEnd(); 
    }
    EXPECT_EQ(arr.lenArr(), 0);
    
    for(int i=0; i<20; ++i) arr.addEnd("y");
    for(int i=0; i<20; ++i) arr.delHead();
    EXPECT_EQ(arr.lenArr(), 0);

    for(int i=0; i<20; ++i) arr.addEnd("z");
    for(int i=0; i<20; ++i) arr.delAt(0);
    EXPECT_EQ(arr.lenArr(), 0);
}

TEST(MyArrTest, Branch_EdgeCases) {
    MyArr arr;
    OutputCapture cap; 

    // Операции с пустым массивом
    arr.readArray();
    arr.delHead();
    arr.delEnd();
    arr.delAt(0);
    arr.repArr(0, "val");
    
    // Неверные индексы 
    arr.addEnd("A");
    arr.addAt(-1, "err");
    arr.addAt(5, "err");
    arr.delAt(-1);
    arr.delAt(5);
    arr.repArr(-1, "err");
    arr.repArr(5, "err");
    
    EXPECT_EQ(arr.getAt(-1), "[INVALID_INDEX]");
    EXPECT_EQ(arr.getAt(5), "[INVALID_INDEX]");

    arr.addHead("Head");
    EXPECT_EQ(arr.getAt(0), "Head");
    
    // Вставка  середину
    arr.addAt(1, "Mid"); 
    EXPECT_EQ(arr.getAt(1), "Mid");

    EXPECT_NE(arr.getData_test(), nullptr);
}

TEST(MyArrTest, IO_Errors_Coverage) {
    MyArr arr;
    
    arr.loadFromFile("no_such_file.arr");
    arr.loadFromBinaryFile("no_such_file.bin");


    {
        ofstream f("corrupt.arr");
        f << "NotANumber"; 
    }
    arr.loadFromFile("corrupt.arr");
    remove("corrupt.arr");

    {
        ofstream f("corrupt.bin", ios::binary);
        int size = 100; 
        f.write((char*)&size, sizeof(size));
        // данные не пишем
    }
    arr.loadFromBinaryFile("corrupt.bin");
    remove("corrupt.bin");
    

    arr.saveToFile(""); 
    arr.saveToBinaryFile("");
}

TEST(MyArrTest, SaveAndLoad_HappyPath) {
    MyArr arr;
    arr.addEnd("1");
    arr.addEnd("2");
    
    arr.saveToFile("good.arr");
    MyArr arr2;
    arr2.loadFromFile("good.arr");
    EXPECT_EQ(arr2.lenArr(), 2);
    EXPECT_EQ(arr2.getAt(0), "1");
    remove("good.arr");

    arr.saveToBinaryFile("good.bin");
    MyArr arr3;
    arr3.loadFromBinaryFile("good.bin");
    EXPECT_EQ(arr3.lenArr(), 2);
    remove("good.bin");
}