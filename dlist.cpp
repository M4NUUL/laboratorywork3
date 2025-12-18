#include "dlist.h"
#include "serialize.h"
using namespace std;

// конструктор
DList::DList() : head(nullptr), tail(nullptr) {
}

// Деструктор
DList::~DList() {
    while (head != nullptr) {
        DNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}

// добавление элемента в начало
void DList::addHead(const string& val) {
    auto node = new DNode(val, head, nullptr);

    if (head != nullptr) 
    {
        head->prev = node;
    } else {
        tail = node;
    }

    head = node; //новая голова
}

//добавление элемента в хвост
void DList::addTail(const string& val) {
    auto node = new DNode(val, nullptr, tail);
    if (tail != nullptr) {
        // если список не пустой то хвост указывает на новый узел
        tail->next = node;
    } else {
        head = node;
    }
    // указатель перемещаем на новый узел
    tail = node;
}

//вставка нового узла перед элементом
void DList::addBefore(const string& target, const string& val) {
    if (head == nullptr) {
        return;
    }
    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        if (curr->value == target) {
            auto node = new DNode(val, curr, curr->prev);
            if (curr->prev != nullptr) {
                curr->prev->next = node;
            } else {
                head = node;
            }
            curr->prev = node;
            return;
        }
    }
}

void DList::addAfter(const string& target, const string& val) {
    if (head == nullptr) {
        return;
    }
    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        if (curr->value == target) {
            auto node = new DNode(val, curr->next, curr);
            if (curr->next != nullptr) {
                curr->next->prev = node;
            } else {
                tail = node;
            }
            curr->next = node;
            return;
        }
    }
}

void DList::delHead() {
    if (head == nullptr) { // проверка на пустоту
        return;
    }
    DNode* tmp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete tmp;
}


void DList::delTail() {
    if (tail == nullptr) {
        return;
    }
    DNode* tmp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete tmp;
}

void DList::delByVal(const string& val) {
    DNode* curr = findValue(val); 
    if (curr == nullptr) {
        return;
    }

    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    } else {
        head = curr->next;
    }

    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    } else {
        tail = curr->prev;
    }

    delete curr;
}

// Приватный метод
auto DList::findValue(const string& val) const -> DNode* {
    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        if (curr->value == val) {
            return curr;
        }
    }
    return nullptr;
}

auto DList::contains(const string& val) const -> bool {
    return findValue(val) != nullptr;
}

void DList::readForward() const {
    if (head == nullptr) {
        cout << "Список пуст" << "\n";
        return;
    }
    cout << "Список вперед: ";
    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        cout << " " << curr->value << " ";
    }
    cout << "\n";
}

void DList::readBackward() const {
    if (tail == nullptr) {
        cout << "Список пуст" << "\n";
        return;
    }

    cout << "Список назад: ";
    for (DNode* curr = tail; curr != nullptr; curr = curr->prev) {
        cout << "\"" << curr->value << "\" ";
    }
    cout << "\n";
}

void DList::delAfterValue(const string& val) {
    DNode* targetNode = findValue(val);
    if (targetNode == nullptr || targetNode->next == nullptr) {
        return;
    }
    delByVal(targetNode->next->value);
}

void DList::delBeforeValue(const string& val) {
    DNode* targetNode = findValue(val);
    if (targetNode == nullptr || targetNode->prev == nullptr) {
        return;
    }
    delByVal(targetNode->prev->value);
}

void DList::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) return;

    int count = 0;
    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        count++;
    }
    file << count << "\n";

    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        writeStringText(file, curr->value);
    }
}

void DList::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;

    while (head != nullptr) {
        delHead();
    }

    int count;
    file >> count;
    string dummy; getline(file, dummy);

    if (file.fail()) return;

    for (int i = 0; i < count; ++i) {
        string val = readStringText(file);
        addTail(val);
    }
}

// --- BINARY ---
void DList::saveToBinaryFile(const string& filename) const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file) {
        return;
    }

    int count = 0;
    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        count++;
    }
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (DNode* curr = head; curr != nullptr; curr = curr->next) {
        writeString(file, curr->value);
    }
}

void DList::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        return;
    }

    while (head != nullptr) {
        delHead();
    }

    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (file.fail()) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        string val = readString(file);
        if (file.fail()) {
            break;
        }
        addTail(val); 
    }
}