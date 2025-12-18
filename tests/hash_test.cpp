#include "gtest/gtest.h"
#include "../hash.h"
#include <sstream>
#include <iostream>
#include <cstdio>

class OutputCapture {
    std::stringstream buffer;
    std::streambuf* old;
public:
    OutputCapture() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~OutputCapture() { std::cout.rdbuf(old); }
    std::string str() const { return buffer.str(); }
};

TEST(HashTest, OpenHash_Insert_Update_DeletedSlot) {
    OpenHash h(3);

    h.insert("A","1");
    h.insert("B","2");
    h.insert("C","3");

    h.insert("A","99");
    EXPECT_EQ(h.find("A"), "99");

    EXPECT_TRUE(h.erase("B"));
    EXPECT_EQ(h.find("B"), "");

    h.insert("X","Y");
    EXPECT_EQ(h.find("X"), "Y");
}

TEST(HashTest, OpenHash_FindErase_NotFound) {
    OpenHash h(3);
    h.insert("A","1");

    EXPECT_EQ(h.find("NOPE"), "");

    EXPECT_FALSE(h.erase("NOPE"));
}

TEST(HashTest, OpenHash_FullTable) {
    OpenHash h(2); 
    h.insert("A", "1");
    h.insert("B", "2");
    
    h.insert("C", "3"); 
    
    EXPECT_EQ(h.find("A"), "1");
    EXPECT_EQ(h.find("B"), "2");
    EXPECT_EQ(h.find("C"), ""); 
}

TEST(HashTest, ChainHash_InsertUpdate) {
    ChainHash h(5);
    h.insert("Key1", "Val1");
    
    h.insert("Key1", "Val2");
    
    EXPECT_EQ(h.find("Key1"), "Val2");
}

TEST(HashTest, ChainHash_CollisionsAndErase) {
    ChainHash h(1);
    h.insert("A", "1");
    h.insert("B", "2");
    h.insert("C", "3");

    EXPECT_EQ(h.find("A"), "1");
    EXPECT_EQ(h.find("B"), "2");
    EXPECT_EQ(h.find("C"), "3");

    EXPECT_TRUE(h.erase("B"));
    EXPECT_EQ(h.find("B"), "");

    h.erase("C");
    EXPECT_EQ(h.find("C"), "");
    
    h.erase("A");
    EXPECT_EQ(h.find("A"), "");
    
    EXPECT_FALSE(h.erase("Z"));
}

TEST(HashTest, ChainHash_ShowEmpty) {
    ChainHash h(5);
    h.show();
    SUCCEED();
}

TEST(HashTest, ChainHash_SaveLoad) {
    std::string fname = "chain_hash.dat";
    {
        ChainHash h(5);
        h.insert("One", "1");
        h.insert("Two", "2");
        h.saveToFile(fname);
    }
    
    {
        ChainHash h(5);
        h.loadFromFile(fname);
        EXPECT_EQ(h.find("One"), "1");
        EXPECT_EQ(h.find("Two"), "2");
        EXPECT_EQ(h.find("Three"), "");
    }
    std::remove(fname.c_str());
}

TEST(HashTest, OpenHash_SaveLoad) {
    std::string fname = "open_hash.dat";
    {
        OpenHash h(5);
        h.insert("Alpha", "100");
        h.insert("Beta", "200");
        h.saveToFile(fname);
    }
    
    {
        OpenHash h(5);
        h.loadFromFile(fname);
        EXPECT_EQ(h.find("Alpha"), "100");
        EXPECT_EQ(h.find("Beta"), "200");
    }
    std::remove(fname.c_str());
}

TEST(HashTest, LoadFromBadFile) {
    ChainHash ch(5);
    ch.loadFromFile("non_existent_file.dat");
    
    OpenHash oh(5);
    oh.loadFromFile("non_existent_file.dat");
}

TEST(HashTest, parse_cmd_CorrectSplits) {
    std::string cmd, arg1, rest;
    parse_cmd("INSERT   key   value", cmd, arg1, rest);
    EXPECT_EQ(cmd, "INSERT");
    EXPECT_EQ(arg1, "key");
    EXPECT_EQ(rest, "value");
}

TEST(HashTest, parse_cmd_LeadingSpaces) {
    std::string cmd, arg1, rest;
    parse_cmd("   SEARCH   A", cmd, arg1, rest);
    
    EXPECT_EQ(cmd, "SEARCH"); 
    EXPECT_EQ(arg1, "A");
}

TEST(HashTest, ChainHash_Collision_DeleteMiddle) {
    ChainHash h(1); 
    h.insert("A", "1");
    h.insert("B", "2");
    h.insert("C", "3");
    

    EXPECT_TRUE(h.erase("B"));
    EXPECT_EQ(h.find("B"), "");
    EXPECT_EQ(h.find("C"), "3");
    EXPECT_EQ(h.find("A"), "1");
    
    EXPECT_TRUE(h.erase("C"));
    EXPECT_EQ(h.find("C"), "");
    EXPECT_EQ(h.find("A"), "1");
}

TEST(HashTest, ChainHash_UpdateValue) {
    ChainHash h(5);
    h.insert("Key", "Val1");
    h.insert("Key", "Val2"); // Обновление
    EXPECT_EQ(h.find("Key"), "Val2");
}

TEST(HashTest, ChainHash_EmptyOps) {
    ChainHash h(5);
    EXPECT_FALSE(h.erase("Missing"));
    EXPECT_EQ(h.find("Missing"), "");
    
    OutputCapture cap;
    h.show();
    EXPECT_NE(cap.str().find("пусто"), std::string::npos);
}


TEST(HashTest, OpenHash_TableFull_WrapAround) {
    OutputCapture cap;
    OpenHash h(2);
    h.insert("A", "1");
    h.insert("B", "2");
    

    h.insert("C", "3"); 
    
    EXPECT_NE(cap.str().find("переполнена"), std::string::npos);
}

TEST(HashTest, OpenHash_Deleted_Reuse) {
    OpenHash h(3);
    h.insert("A", "1");
    h.insert("B", "2");
    
    h.erase("A");
    EXPECT_EQ(h.find("A"), "");
    
    h.insert("C", "3");
    EXPECT_EQ(h.find("C"), "3");
    
    EXPECT_EQ(h.find("B"), "2");
}

TEST(HashTest, OpenHash_Loop_NotFound) {
    OpenHash h(3);
    h.insert("A", "1");
    EXPECT_EQ(h.find("Z"), "");
    EXPECT_FALSE(h.erase("Z"));
}

TEST(HashTest, Hash_IO_Errors) {
    ChainHash ch(5);
    ch.saveToFile(""); 
    ch.loadFromFile("missing.txt");
    
    OpenHash oh(5);
    oh.saveToBinaryFile("");
    oh.loadFromBinaryFile("missing.bin");
}

TEST(HashTest, Hash_Cmd_Parse) {
    std::string cmd, a1, rest;
    // Тест парсинга с лишними пробелами
    parse_cmd("  INSERT   Key   Value With Space  ", cmd, a1, rest);
    EXPECT_EQ(cmd, "INSERT");
    EXPECT_EQ(a1, "Key");
    EXPECT_EQ(rest, "Value With Space  ");
}

TEST(HashTest, hash_man_scripted) {
    std::stringstream fake_in;
    fake_in 
        << "INSERT A 1\n"
        << "SEARCH A\n"
        << "DELETE A\n"
        << "SHOW\n"
        << "BACK\n";

    std::streambuf* old_in = std::cin.rdbuf(fake_in.rdbuf());
    OutputCapture cap;
    hash_man();
    std::cin.rdbuf(old_in);

    EXPECT_NE(cap.str().find("УПРАВЛЕНИЕ"), std::string::npos);
    EXPECT_NE(cap.str().find("Выход"), std::string::npos);
}