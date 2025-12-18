#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Stack {
private:
    class SNode {
    public:
        string value;  // значение элемента
        SNode* next;   // ссылка на следующий элемент
    };

    SNode* top;  //указатель на верхушку стека

public:
    Stack();

    ~Stack();

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(Stack&&) = delete;

    void push(string val);

    string peek() const;

    string pop();

    void readStack() const;
    bool isEmpty() const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

    // Бинарный
    void saveToBinaryFile(const string& filename) const;
    void loadFromBinaryFile(const string& filename);

    SNode* getTop_test() const  
    {
        return top;
    }
};


#endif