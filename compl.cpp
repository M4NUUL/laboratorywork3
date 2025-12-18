#include "compl.h"
#include <iostream>
#include <fstream>      
#include <string>       
#include <functional>   
using namespace std;


// Конструктор
CompleteBinaryTree::CompleteBinaryTree() : root(nullptr), size(0) {}

// Деструктор
CompleteBinaryTree::~CompleteBinaryTree() {
    clear();
}

//Рекурсивное удаление дерева
void CompleteBinaryTree::deleteTreeRecursive(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteTreeRecursive(node->left);
    deleteTreeRecursive(node->right);
    delete node;
}

//Поиск узла с минимальным значением
TreeNode* CompleteBinaryTree::findMin(TreeNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

//Рекурсивное удаление узла
TreeNode* CompleteBinaryTree::deleteNodeRecursive(TreeNode* current, int value) {
    if (current == nullptr) {
        return nullptr;
    }

    if (value < current->data) {
        // Идем влево
        current->left = deleteNodeRecursive(current->left, value);
    } else if (value > current->data) {
        // Идем вправо
        current->right = deleteNodeRecursive(current->right, value);
    } else {
        // Узел найден
        
        //Нет левого потомка
        if (current->left == nullptr) {
            TreeNode* temp = current->right;
            delete current;
            size--; 
            return temp;
        }
        //Нет правого потомка
        else if (current->right == nullptr) {
            TreeNode* temp = current->left;
            delete current;
            size--;
            return temp;
        }


        TreeNode* successor = findMin(current->right);

        current->data = successor->data;

      
        current->right = deleteNodeRecursive(current->right, successor->data);
    }
    return current;
}

// Проверка на пустоту
bool CompleteBinaryTree::isEmpty() const {
    return root == nullptr;
}

// Очистка дерева
void CompleteBinaryTree::clear() {
    if (root != nullptr) {
        deleteTreeRecursive(root);
        root = nullptr;
        size = 0;
    }
}

// Вставка элемента
void CompleteBinaryTree::insert(int value) {
    TreeNode* newNode = new TreeNode(value);

    if (root == nullptr) {
        root = newNode;
        size++;
        return;
    }

    TreeNode* current = root;
    while (true) {
        if (value < current->data) {
            if (current->left == nullptr) {
                current->left = newNode;
                size++;
                return;
            }
            current = current->left;
        } else if (value > current->data) {
            if (current->right == nullptr) {
                current->right = newNode;
                size++;
                return;
            }
            current = current->right;
        } else {
            delete newNode;
            return;
        }
    }
}

// Удаление элемента 
void CompleteBinaryTree::remove(int value) {
    if (isEmpty()) {
        std::cout << "Нельзя удалить из пустого дерева." << std::endl;
        return;
    }

    int initialSize = size;
    root = deleteNodeRecursive(root, value);

    if (size < initialSize) {
        std::cout << "Элемент " << value << " удален." << std::endl;
    } else {
        std::cout << "Элемент " << value << " не найден." << std::endl;
    }
}

// Поиск элемента
bool CompleteBinaryTree::search(int value) const {
    if (isEmpty()) {
        return false;
    }
    TreeNode* current = root;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

void CompleteBinaryTree::printTreeUtil(TreeNode* node, const std::string& prefix, bool isLast) const {
    if (node == nullptr) {
        return;
    }

    std::cout << prefix;
    if (isLast) {
        std::cout << "└──";
    } else {
        std::cout << "├──";
    }
    std::cout << node->data << std::endl;

    std::string childPrefix = prefix;
    if (isLast) {
        childPrefix += "    ";
    } else {
        childPrefix += "│   ";
    }

    if (node->left != nullptr && node->right != nullptr) {
        printTreeUtil(node->left, childPrefix, false);
        printTreeUtil(node->right, childPrefix, true);
    } else if (node->left != nullptr) {
        printTreeUtil(node->left, childPrefix, true);
    } else if (node->right != nullptr) {
        printTreeUtil(node->right, childPrefix, true);
    }
}

void CompleteBinaryTree::print() const {
    if (isEmpty()) {
        std::cout << "Дерево пустое." << std::endl;
        return;
    }
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Дерево (размер: " << size << "):" << std::endl;

    std::cout << root->data << std::endl;

    if (root->left != nullptr && root->right != nullptr) {
        printTreeUtil(root->left, "", false);
        printTreeUtil(root->right, "", true);
    } else if (root->left != nullptr) {
        printTreeUtil(root->left, "", true);
    } else if (root->right != nullptr) {
        printTreeUtil(root->right, "", true);
    }

    std::cout << "------------------------------------------" << std::endl;
}

int CompleteBinaryTree::getSize() const {
    return size;
}

void CompleteBinaryTree::saveToFile(std::ofstream& out) const {
    std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) {
            out << "# ";
            return;
        }
        out << node->data << " ";
        dfs(node->left);
        dfs(node->right);
    };
    dfs(root);
}

void CompleteBinaryTree::loadFromFile(std::ifstream& in) {
    clear();
    std::function<TreeNode*()> dfs = [&]() -> TreeNode* {
        std::string token;
        if (!(in >> token)) return nullptr;
        if (token == "#") return nullptr;
        int v = std::stoi(token);
        TreeNode* node = new TreeNode(v);
        size++;
        node->left = dfs();
        node->right = dfs();
        return node;
    };
    root = dfs();
}

void CompleteBinaryTree::saveToBinaryFile(std::ofstream& out) const {
    std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) {
            int marker = -1;
            out.write((char*)&marker, sizeof(marker));
            return;
        }
        out.write((char*)&node->data, sizeof(node->data));
        dfs(node->left);
        dfs(node->right);
    };
    dfs(root);
}

void CompleteBinaryTree::loadFromBinaryFile(std::ifstream& in) {
    clear();
    std::function<TreeNode*()> dfs = [&]() -> TreeNode* {
        int v;
        if (!in.read((char*)&v, sizeof(v))) return nullptr;
        if (v == -1) return nullptr;

        TreeNode* node = new TreeNode(v);
        size++;

        node->left = dfs();
        node->right = dfs();
        return node;
    };
    root = dfs();
}


void CompleteBinaryTree::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) return;
    saveToFile(file);
}

void CompleteBinaryTree::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return;
    loadFromFile(file);
}

void CompleteBinaryTree::saveToBinaryFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) return;
    saveToBinaryFile(file);
}

void CompleteBinaryTree::loadFromBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return;
    loadFromBinaryFile(file);
}