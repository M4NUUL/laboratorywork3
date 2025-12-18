#include "gtest/gtest.h"
#include "../dlist.h"
#include "../serialize.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class OutputCapture {
    std::stringstream buffer;
    std::streambuf* prev;
public:
    OutputCapture() : prev(std::cout.rdbuf(buffer.rdbuf())) {}
    ~OutputCapture() { std::cout.rdbuf(prev); }
    std::string str() { return buffer.str(); }
};

TEST(DListTest, Branch_Killer) {
    DList d;


    d.addHead("A"); 
    d.addHead("B"); 


    d.delHead(); 
    EXPECT_EQ(d.getHead_Test()->value, "A");


    d.addTail("Z"); 
    d.delTail();
    EXPECT_EQ(d.getTail_Test()->value, "A");

    
    d.addTail("C"); 
    d.addAfter("A", "B"); 

    EXPECT_TRUE(d.contains("B"));
}

TEST(DListTest, Coverage_Empty_Ops) {
    DList d;
    d.delHead();
    d.delTail();
    d.delByVal("A");
    d.delAfterValue("A");
    d.delBeforeValue("A");
    d.addAfter("A", "B");
    d.addBefore("A", "B");
    
    EXPECT_FALSE(d.contains("A"));
}

TEST(DListTest, Coverage_SingleElement_Transitions) {
    DList d;
    
    d.addHead("A");
    d.delHead();
    EXPECT_EQ(d.getHead_Test(), nullptr);
    EXPECT_EQ(d.getTail_Test(), nullptr);
    
    d.addHead("B");
    d.delTail();
    EXPECT_EQ(d.getHead_Test(), nullptr);
    EXPECT_EQ(d.getTail_Test(), nullptr);
}

TEST(DListTest, Coverage_AddBefore_AddAfter_Complex) {
    DList d;
    d.addTail("A");
    d.addTail("C");
    
    d.addBefore("C", "B");
 
    OutputCapture cap;
    d.readForward();
    string out = cap.str();
    
    EXPECT_NE(out.find(" B "), string::npos); 
    
    d.addBefore("A", "Start");
    EXPECT_EQ(d.getHead_Test()->value, "Start");
    
    d.addAfter("C", "End");
    EXPECT_EQ(d.getTail_Test()->value, "End");
}

TEST(DListTest, Coverage_DelByVal_Branches) {
    DList d;
    d.addTail("1");
    d.addTail("2");
    d.addTail("3");
    
    d.delByVal("2");
    EXPECT_FALSE(d.contains("2"));
    
    d.delByVal("1");
    EXPECT_EQ(d.getHead_Test()->value, "3");
    
    d.delByVal("3");
    EXPECT_EQ(d.getHead_Test(), nullptr);
    
    d.addTail("X");
    d.delByVal("Y");
    EXPECT_TRUE(d.contains("X"));
}

TEST(DListTest, Coverage_DelAfter_DelBefore_Boundary) {
    DList d;
    d.addTail("A");
    d.addTail("B");
    
    d.delBeforeValue("B"); 
    EXPECT_FALSE(d.contains("A"));
    EXPECT_EQ(d.getHead_Test()->value, "B");
    
    d.delBeforeValue("B"); 
    EXPECT_EQ(d.getHead_Test()->value, "B");
    
    d.delAfterValue("B"); 
    EXPECT_TRUE(d.contains("B"));
    
    d.addTail("C");
    d.delAfterValue("B"); 
    EXPECT_FALSE(d.contains("C"));
}

TEST(DListTest, Coverage_IO) {
    DList d;
    d.saveToFile(""); 
    d.saveToBinaryFile("");
    
    d.loadFromFile("missing.txt");
    d.loadFromBinaryFile("missing.bin");
    
    {
        ofstream f("bad.bin", ios::binary);
        int count = 5;
        f.write((char*)&count, sizeof(count));
        f.close();
    }
    d.loadFromBinaryFile("bad.bin");
    remove("bad.bin");
}