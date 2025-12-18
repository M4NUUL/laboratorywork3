#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std; 

class Queue {
private:
    class QNode {
    public:
        string data;
        QNode* next;
    };

    QNode* front; //указатель на начало
    QNode* rear;  //указатель на конец

public:
    Queue();

    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator=(Queue&&) = delete;

    bool isEmpty() const;

    // Добавление в конец
    void push(string val);

    string pop();
    string peek() const;

    void print() const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

    // Бинарный
    void saveToBinaryFile(const string& filename) const;
    void loadFromBinaryFile(const string& filename);

    QNode* getFront_test() const
    {
        return front;
    }
};


#endif