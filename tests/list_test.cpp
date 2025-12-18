#include "gtest/gtest.h"
#include "../list.h"
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

TEST(MyListTest, Branch_Deletions) {
    MyList list;
    OutputCapture cap;

    list.delTail();
    list.addHead("A");
    list.delTail();
    EXPECT_EQ(list.getHead_test(), nullptr);
    
    list.addTail("A");
    list.addTail("B");
    list.delTail();
    EXPECT_EQ(list.getHead_test()->value, "A");

    list.delByValue("Z");
    list.delByValue("A");
    EXPECT_EQ(list.getHead_test(), nullptr);

    list.addTail("X"); list.addTail("Y");
    list.delByValue("Y");
    EXPECT_FALSE(list.findValue("Y"));
}

TEST(MyListTest, Branch_AdvancedOps) {
    MyList list;
    OutputCapture cap;
    
    list.delAfterValue("A"); 
    list.addTail("A");
    list.delAfterValue("A"); 
    list.addTail("B");
    list.delAfterValue("Z"); 
    list.delAfterValue("A"); 
    EXPECT_FALSE(list.findValue("B"));

    list.delBeforeValue("A");
    list.addHead("A");
    list.delBeforeValue("A"); 
    
    MyList l2;
    l2.addTail("1"); l2.addTail("2"); l2.addTail("3");
    l2.delBeforeValue("2"); 
    EXPECT_EQ(l2.getHead_test()->value, "2");

    MyList l3;
    l3.addTail("X"); l3.addTail("Y"); l3.addTail("Z"); l3.addTail("W");
    l3.delBeforeValue("W"); 
    EXPECT_FALSE(l3.findValue("Z"));
    
    l3.readBack();
}

TEST(MyListTest, AddBeforeHeadValue) {
    OutputCapture cap;
    MyList l;
    l.addBefore("A", "B");
    l.addHead("A");
    l.addBefore("A", "Z"); 
    EXPECT_EQ(l.getHead_test()->value, "Z");
}

TEST(MyListTest, AddAfterNotFound) {
    OutputCapture cap;
    MyList l;
    l.addTail("A");
    l.addAfter("Z", "B"); 
}

TEST(MyListTest, DelByValueEmpty) {
    OutputCapture cap;
    MyList l;
    l.delByValue("A"); 
}

TEST(MyListTest, DelTailMultiple) {
    OutputCapture cap;
    MyList l;
    l.addTail("A"); l.addTail("B"); l.addTail("C");
    l.delTail(); 
    EXPECT_TRUE(l.findValue("B"));
    EXPECT_FALSE(l.findValue("C"));
}

TEST(ListTest, BranchBooster_ComplexConditions) {
    OutputCapture cap;
    MyList l;

    l.delAfterValue("A"); 
    l.addHead("A");
    l.delAfterValue("A"); 

    l.addTail("B");
    l.delAfterValue("Z");
    l.delAfterValue("B");
    
    MyList l2;
    l2.delBeforeValue("A"); 
    l2.addHead("A");
    l2.delBeforeValue("A");

    l2.addTail("B");
    l2.delBeforeValue("B"); 
    EXPECT_EQ(l2.getHead_test()->value, "B");

    MyList l3;
    l3.addTail("A"); l3.addTail("B"); l3.addTail("C");
    l3.delBeforeValue("Z");

    MyList l4;
    l4.addTail("A"); l4.addTail("B");
    l4.delBeforeValue("Z");
}

TEST(DestructorTest, MyListCleanup) {
    OutputCapture cap;
    {
        MyList l;
        l.addTail("1");
        l.addTail("2");
    }
}

TEST(MyListTest, Coverage_EmptyPrints) {
    MyList l;
    OutputCapture cap;
    
    l.readForward();
    l.readBack();
    
    string out = cap.str();
    EXPECT_TRUE(out.find("пуст") != string::npos);
}

TEST(MyListTest, Coverage_DelHeadEmpty) {
    MyList l;
    l.delHead(); 
    EXPECT_EQ(l.getHead_test(), nullptr);
}

TEST(MyListTest, Coverage_Serialization_Fail) {
    MyList l;
    
    l.saveToFile(""); 

    l.loadFromFile("non_existent_file_123.dat");
}

TEST(MyListTest, Coverage_Load_Corrupted) {
    MyList l;
    
    {
        ofstream f("corrupted_list.dat", ios::binary);
        int count = 5;
        f.write((char*)&count, sizeof(count));
        f.close();
    }
    
    l.loadFromFile("corrupted_list.dat");
    
    remove("corrupted_list.dat");
}

TEST(MyListTest, Coverage_Delete_From_Empty) {
    MyList list;
    OutputCapture cap;
    
    // Пытаемся удалить из пустого
    list.delHead();
    list.delTail();
    list.delByValue("A");
    list.delAfterValue("A");
    list.delBeforeValue("A");
    
    string out = cap.str();
    EXPECT_NE(out.find("пуст"), string::npos); // Проверяем вывод ошибки
}

TEST(MyListTest, Coverage_Add_EdgeCases) {
    MyList list;
    OutputCapture cap;
    
    // addBefore в пустой список
    list.addBefore("Target", "Val"); 
    EXPECT_EQ(list.getHead_test(), nullptr);

    list.addAfter("Target", "Val");
    EXPECT_NE(cap.str().find("пуст"), string::npos);
    
    list.addTail("A");
    list.addBefore("A", "NewHead");
    EXPECT_EQ(list.getHead_test()->value, "NewHead");
    
    list.addAfter("NonExistent", "X");
    
    list.addBefore("NonExistent", "X");
}

TEST(MyListTest, Coverage_Delete_Head_Tail_SingleElement) {
    MyList list;
    list.addHead("Single");
    

    list.delTail();
    EXPECT_EQ(list.getHead_test(), nullptr);
    
    list.addHead("Single2");
    list.delHead();
    EXPECT_EQ(list.getHead_test(), nullptr);
}

TEST(MyListTest, Coverage_DelByValue_Cases) {
    MyList list;
    OutputCapture cap;
    
    list.addTail("A");
    list.addTail("B");
    list.addTail("C");
    
    // Удаляем голову по значению
    list.delByValue("A");
    EXPECT_FALSE(list.findValue("A"));
    EXPECT_EQ(list.getHead_test()->value, "B");
    
    // Удаляем несуществующий
    list.delByValue("Z");
    EXPECT_NE(cap.str().find("не найден"), string::npos);
    
    // Удаляем хвост по значению
    list.delByValue("C");
    EXPECT_FALSE(list.findValue("C"));
}

TEST(MyListTest, Coverage_DelAfter_DelBefore) {
    MyList list;
    
    list.addTail("A");
    list.delAfterValue("A"); 
    
    list.addTail("B");
    list.delAfterValue("A");
    EXPECT_FALSE(list.findValue("B"));
    
    list.delHead();
    list.addTail("1");
    list.addTail("2");
    list.addTail("3");
    
    list.delBeforeValue("3");
    EXPECT_FALSE(list.findValue("2"));
    
    list.delBeforeValue("1");
    EXPECT_TRUE(list.findValue("1"));
    
    list.delBeforeValue("3"); 
    EXPECT_FALSE(list.findValue("1"));
}

TEST(MyListTest, Coverage_IO_Failures) {
    MyList list;
    // Запись в недоступный файл
    list.saveToFile("");
    
    // Чтение из несуществующего
    list.loadFromFile("does_not_exist.txt");
    EXPECT_EQ(list.getHead_test(), nullptr);
    
    // Чтение битого файла
    {
        ofstream f("broken_list.txt");
        f << "NotANumber";
        f.close();
    }
    list.loadFromFile("broken_list.txt");
    remove("broken_list.txt");
}

TEST(MyListTest, Coverage_Load_Overwrite) {
    MyList l;
    l.addTail("Old1");
    l.addTail("Old2");
    
    remove("good_list.dat");

    {
        ofstream f("good_list.dat"); 
        if (f.is_open()) {
            f << "1\n";      
            f << "New\n";  
            f.close();
        }
    }
    
    l.loadFromFile("good_list.dat");
    
   
    ASSERT_NE(l.getHead_test(), nullptr);
    EXPECT_EQ(l.getHead_test()->value, "New");
    EXPECT_EQ(l.getHead_test()->next, nullptr);
    
    remove("good_list.dat");
}