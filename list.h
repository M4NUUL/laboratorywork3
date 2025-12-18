#ifndef LIST_H
#define LIST_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std; 

class MyList {
private:
    class Node {
    public:
        string value; 
        Node* next;   

        Node(const string& v, Node* n) : value(v), next(n) {}
    };

    Node* head; 

    void printBack(Node* node) const;

public:
    MyList();
    ~MyList();

    MyList(const MyList&) = delete;
    MyList& operator=(const MyList&) = delete;
    MyList(MyList&&) = delete;
    MyList& operator=(MyList&&) = delete;

    void addHead(const string& val);
    void addTail(const string& val);
    void delHead();
    void addAfter(const string& target, const string& val);
    void addBefore(const string& target, const string& val);
    void delTail();
    void delByValue(const string& val);
    bool findValue(const string& val) const; 
    void readForward() const;
    void readBack() const;
    void delAfterValue(const string& val);
    void delBeforeValue(const string& val);
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

    // Бинарный
    void saveToBinaryFile(const string& filename) const;
    void loadFromBinaryFile(const string& filename);
    Node* getHead_test() const {
        return head;
    }
};


#endif