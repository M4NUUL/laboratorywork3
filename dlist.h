#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class DList {
private:
    // cтруктура узла двусвязного списка 
    class DNode {
    public:
        string value;   // значение узла
        DNode* next;    // указатель на следующий элемент
        DNode* prev;    // указатель на предыдущий элемент

        DNode(const string& v, DNode* n, DNode* p) : value(v), next(n), prev(p) {}
    };

    DNode* head; // указатель на первый элемент
    DNode* tail; // указатель на последний элемент

    auto findValue(const string& val) const -> DNode*;

public:
    //конструктор 
    DList();

    // Деструктор 
    ~DList();


    DList(const DList&) = delete;
    DList& operator=(const DList&) = delete;
    DList(DList&&) = delete;
    DList& operator=(DList&&) = delete;

    void addHead(const string& val);

    void addTail(const string& val);

    void addBefore(const string& target, const string& val);

    void addAfter(const string& target, const string& val);

    void delHead();

    void delTail();

    void delByVal(const string& val);
    auto contains(const string& val) const -> bool;

    void readForward() const;

    void readBackward() const;

    void delAfterValue(const string& val);

    void delBeforeValue(const string& val);

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

    void saveToBinaryFile(const string& filename) const;
    void loadFromBinaryFile(const string& filename);
  
  
    DNode* getHead_Test() const
    {
        return head;
    }
    DNode* getTail_Test()const 
    {
        return tail;
    }
};

#endif