#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <fstream>

// Класс узла дерева
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    //конструктор узла
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Основной класс дерева
class CompleteBinaryTree {
private:
    TreeNode* root;
    int size;

    void deleteTreeRecursive(TreeNode* node);
    TreeNode* findMin(TreeNode* node);
    TreeNode* deleteNodeRecursive(TreeNode* current, int value);
    void printTreeUtil(TreeNode* node, const std::string& prefix, bool isLast) const;

public:
    // Конструктор и деструктор
    CompleteBinaryTree();
    ~CompleteBinaryTree();

    // Публичные методы интерфейса
    bool isEmpty() const;
    void clear();
    void insert(int value);
    void remove(int value); 
    bool search(int value) const;
    void print() const;
    int getSize() const;

    void saveToFile(std::ofstream& out) const;
    void loadFromFile(std::ifstream& in);
    void saveToBinaryFile(std::ofstream& out) const;
    void loadFromBinaryFile(std::ifstream& in);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void saveToBinaryFile(const std::string& filename) const;
    void loadFromBinaryFile(const std::string& filename);
};

#endif