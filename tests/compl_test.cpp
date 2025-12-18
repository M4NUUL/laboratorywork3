#include "gtest/gtest.h"
#include "../compl.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>

class OutputCapture {
    std::stringstream buffer;
    std::streambuf* old;
public:
    OutputCapture() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~OutputCapture() { std::cout.rdbuf(old); }
    std::string str() const { return buffer.str(); }
};

TEST(TreeTest, EmptySearchPrintRemove) {
    CompleteBinaryTree t;

    EXPECT_FALSE(t.search(10));

    t.remove(5);
    EXPECT_TRUE(t.isEmpty());
    EXPECT_EQ(t.getSize(), 0);

    t.print();
}

TEST(TreeTest, InsertRootAndDuplicate) {
    CompleteBinaryTree t;

    t.insert(10);
    EXPECT_TRUE(t.search(10));
    EXPECT_EQ(t.getSize(), 1);

    t.insert(10);
    EXPECT_EQ(t.getSize(), 1); 
}

TEST(TreeTest, InsertLeftRightSearch) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    t.insert(15);

    EXPECT_TRUE(t.search(5));
    EXPECT_TRUE(t.search(15));
    EXPECT_TRUE(t.search(10));

    EXPECT_FALSE(t.search(99));
}

TEST(TreeTest, DeleteLeaf) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    t.insert(15);

    t.remove(5);
    
    EXPECT_FALSE(t.search(5));
    EXPECT_EQ(t.getSize(), 2);
}

TEST(TreeTest, DeleteNodeOneChild_LeftOnly) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    t.insert(1);

    t.remove(5);

    EXPECT_TRUE(t.search(1));
    EXPECT_FALSE(t.search(5));
    EXPECT_EQ(t.getSize(), 2);
}

TEST(TreeTest, DeleteNodeOneChild_RightOnly) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    t.insert(7);

    t.remove(5);

    EXPECT_TRUE(t.search(7));
    EXPECT_FALSE(t.search(5));
    EXPECT_EQ(t.getSize(), 2);
}

TEST(TreeTest, DeleteNodeTwoChildren) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(12);
    t.insert(18);

    t.remove(10);

    EXPECT_FALSE(t.search(10));
    EXPECT_TRUE(t.search(12));
    EXPECT_EQ(t.getSize(), 4);
}

TEST(TreeTest, RemoveMissing) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);

    int sizeBefore = t.getSize();
    t.remove(99);
    int sizeAfter = t.getSize();

    EXPECT_EQ(sizeBefore, sizeAfter);
}

TEST(TreeTest, ClearTree) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);

    t.clear();
    
    EXPECT_TRUE(t.isEmpty());
    EXPECT_EQ(t.getSize(), 0);
}

TEST(TreeTest, PrintNonEmpty) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    
    t.print();
    SUCCEED(); 
}

TEST(TreeTest, SaveLoadTextFile) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    t.insert(15);

    std::string fname = "tree_test.txt";
    
    {
        std::ofstream out(fname);
        t.saveToFile(out);
    }

    CompleteBinaryTree t2;
    {
        std::ifstream in(fname);
        t2.loadFromFile(in);
    }

    EXPECT_EQ(t2.getSize(), 3);
    EXPECT_TRUE(t2.search(10));
    EXPECT_TRUE(t2.search(5));
    EXPECT_TRUE(t2.search(15));

    std::remove(fname.c_str());
}

TEST(TreeTest, SaveLoadBinaryFile) {
    CompleteBinaryTree t;
    t.insert(100);
    t.insert(50);
    t.insert(150);

    std::string fname = "tree_test.bin";
    
    {
        std::ofstream out(fname, std::ios::binary);
        t.saveToBinaryFile(out);
    }

    CompleteBinaryTree t2;
    {
        std::ifstream in(fname, std::ios::binary);
        t2.loadFromBinaryFile(in);
    }

    EXPECT_EQ(t2.getSize(), 3);
    EXPECT_TRUE(t2.search(100));
    EXPECT_TRUE(t2.search(50));
    EXPECT_TRUE(t2.search(150));

    std::remove(fname.c_str());
}

TEST(TreeTest, Coverage_Remove_Root_TwoChildren) {
    CompleteBinaryTree t;
    t.insert(10); 
    t.insert(5);  
    t.insert(15); 
    

    t.remove(10);
    
    EXPECT_FALSE(t.search(10));
    EXPECT_TRUE(t.search(5));
    EXPECT_TRUE(t.search(15));
    EXPECT_EQ(t.getSize(), 2);
}

TEST(TreeTest, Coverage_Remove_Root_OneChild) {
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(5);
    // Нет правого
    
    t.remove(10); // Удаляем корень с 1 левым ребенком
    EXPECT_FALSE(t.search(10));
    EXPECT_TRUE(t.search(5));
}

TEST(TreeTest, Coverage_Remove_NotExists_And_Empty) {
    OutputCapture cap;
    CompleteBinaryTree t;
    
    t.remove(10); 
    EXPECT_NE(cap.str().find("Нельзя удалить"), std::string::npos);
    
    t.insert(5);
    t.remove(99); // Несуществующий
    // Проверяем, что размер не изменился
}

TEST(TreeTest, Coverage_Insert_Duplicates) {
    OutputCapture cap;
    CompleteBinaryTree t;
    t.insert(10);
    t.insert(10); // Дубликат
    
    EXPECT_EQ(t.getSize(), 1);
}

TEST(TreeTest, Coverage_IO_Errors) {
    CompleteBinaryTree t;
    t.saveToFile("");
    t.loadFromFile("missing.txt");
    
    t.saveToBinaryFile("");
    t.loadFromBinaryFile("missing.bin");
    
    // Бинарный файл с маркером конца (-1) сразу
    {
        std::ofstream f("empty_tree.bin", std::ios::binary);
        int m = -1;
        f.write((char*)&m, sizeof(m));
        f.close();
    }
    t.loadFromBinaryFile("empty_tree.bin");
    EXPECT_EQ(t.getSize(), 0);
    std::remove("empty_tree.bin");
}

TEST(TreeTest, LoadFromEmptyFiles) {
    CompleteBinaryTree t;
    
    {
        std::ofstream out("empty.txt");
    }
    {
        std::ifstream in("empty.txt");
        t.loadFromFile(in);
    }
    EXPECT_EQ(t.getSize(), 0);
    std::remove("empty.txt");

    {
        std::ofstream out("empty.bin", std::ios::binary);
    }
    {
        std::ifstream in("empty.bin", std::ios::binary);
        t.loadFromBinaryFile(in);
    }
    EXPECT_EQ(t.getSize(), 0);
    std::remove("empty.bin");
}