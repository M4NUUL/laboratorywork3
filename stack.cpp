#include "stack.h"
#include "serialize.h"
using namespace std;

// Конструктор
Stack::Stack() : top(nullptr) {
}

// Деструктор
Stack::~Stack() {
    while (top) {
        SNode* tmp = top;
        top = top->next;
        delete tmp;
    }
}

void Stack::push(string val) {
    SNode* node = new SNode;
    node->value = val;
    node->next = top;
    top = node;
}

//извлекает элмент из стека и возвращает его тому, кто вызвал
string Stack::pop() {
    if (!top) {
        return "[STACK_EMPTY]";
    }
    SNode* tmp = top;
    string val = tmp->value;
    top = top->next;
    delete tmp;
    return val;
}

//чтение без удаления
string Stack::peek() const {
    if (!top) {
        return "[STACK_EMPTY]";
    }
    return top->value;
}

bool Stack::isEmpty() const { 
    return top == nullptr;
}

void Stack::readStack() const {
    if (!top) {
        cout << "Стек пуст" << "\n";
        return;
    }
    cout << "Содержимое стека (сверху вниз): " << "\n";
    for (SNode* curr = top; curr; curr = curr->next) {
        cout << "  " << curr->value << "\n";
    }
}




void Stack::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) return;

    int count = 0;
    for (SNode* curr = top; curr; curr = curr->next) {
        count++;
    }
    file << count << "\n";

    // Сохраняем в обратном порядке, чтобы при загрузке порядок восстановился
    SNode* curr = top;
    string* tempArr = new string[count];
    for (int i = count - 1; i >= 0; --i) {
        tempArr[i] = curr->value;
        curr = curr->next;
    }

    for (int i = 0; i < count; ++i) {
        writeStringText(file, tempArr[i]);
    }
    delete[] tempArr;
}

void Stack::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;

    while (!isEmpty()) pop();

    int count;
    file >> count;
    string dummy; getline(file, dummy);

    for (int i = 0; i < count; ++i) {
        push(readStringText(file));
    }
}

void Stack::saveToBinaryFile(const string& filename) const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file) return;

    int count = 0;
    for (SNode* curr = top; curr; curr = curr->next) {
        count++;
    }
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    SNode* curr = top;
    string* tempArr = new string[count];
    for (int i = count - 1; i >= 0; --i) {
        tempArr[i] = curr->value;
        curr = curr->next;
    }

    for (int i = 0; i < count; ++i) {
        writeString(file, tempArr[i]);
    }
    delete[] tempArr;
}

void Stack::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return;

    while (!isEmpty()) pop();

    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (file.fail()) return;

    for (int i = 0; i < count; ++i) {
        string val = readString(file);
        if (file.fail()) break;
        push(val); 
    }
}