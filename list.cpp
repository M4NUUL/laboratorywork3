#include "serialize.h"
#include "list.h"

using namespace std;

// Конструктор
MyList::MyList() : head(nullptr) {
}

// Деструктор
MyList::~MyList() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr; 
}

void MyList::addHead(const string& val) {
    Node* node = new Node(val, head);
    head = node;
}

//добавление в конец
void MyList::addTail(const string& val) {
    Node* node = new Node(val, nullptr);
    if (!head) {
        head = node;
        return;
    }

    Node* cur = head; //указатель на узел
    while (cur->next)
        cur = cur->next;
    cur->next = node;
}

//вставка нового элемента преед узлом
void MyList::addBefore(const string& target, const string& val) {
    if (!head) {
        return;
    }

    if (head->value == target) {
        addHead(val);
        return;
    }

    Node* cur = head;
    //ищет следующий узел и останавливаем когда будет прямо перед целевым
    while (cur->next && cur->next->value != target) {
        cur = cur->next;
    }

    if (!cur->next) {
        cout << "Элемент не найден" << "\n";
        return;
    }
    //если узел найден создаем указатель на новый узел
    Node* node = new Node(val, cur->next);
    cur->next = node;
}

//вставка после узла со значением
void MyList::addAfter(const string& target, const string& val) {
    if (!head) {
        cout << "Список пуст" << "\n";
        return;
    }

    Node* cur = head;
    while (cur && cur->value != target) {
        cur = cur->next;
    }
    if (!cur) {
        cout << "Элемент не найден" << "\n";
        return;
    }

    Node* node = new Node(val, cur->next);
    cur->next = node;
}

//удалить последний элемент списка
void MyList::delTail() {
    if (!head) {
        cout << "Список пуст" << "\n";
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }

    Node* cur = head;
    while (cur->next->next) //ищем предпоследний элемент
        cur = cur->next; 

    delete cur->next; //освобождаем память посленего узла
    cur->next = nullptr; //делаем новый конец списка
}

//удаляем узел по заданному значению
void MyList::delByValue(const string& val) {
    if (!head) {
        cout << "Список пуст." << "\n";
        return;
    }
    if (head->value == val) {
        delHead();
        cout << "Элемент " << val << " удален." << "\n";
        return;
    }
    Node* cur = head;
    while (cur->next && cur->next->value != val) {
        cur = cur->next;
    }
    if (!cur->next) {
        cout << "Элемент " << val << " не найден." << "\n";
        return;
    }
    Node* tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
    cout << "Элемент " << val << " удален." << "\n";
}

//поиск элементта и вывод его значения
bool MyList::findValue(const string& val) const {
    Node* curr = head;
    while (curr) {
        if (curr->value == val) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

//вывод в обычном
void MyList::readForward() const {
    if (!head) {
        cout << "Список пуст" << endl;
        return;
    }
    cout << "Список вперёд: ";
    for (Node* curr = head; curr; curr = curr->next) {
        cout << "\"" << curr->value << "\" ";
    }
    cout << endl;
}

void MyList::printBack(Node* node) const {
    if (!node)
        return;
    printBack(node->next);
    cout << "\"" << node->value << "\" ";
}

void MyList::readBack() const {
    if (!head) {
        cout << "Список пуст" << "\n";
        return;
    }
    cout << "Список (назад): ";
    printBack(head);
    cout << endl;
}

void MyList::delHead() {
    if (!head) return;
    Node* tmp = head;
    head = head->next;
    delete tmp;
}

void MyList::delAfterValue(const string& val) {
    if (!head || !head->next) return;
    Node* cur = head;
    while (cur && cur->value != val) {
        cur = cur->next;
    }
    if (!cur || !cur->next) return;
    Node* tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
}

void MyList::delBeforeValue(const string& val) {
    if (!head || !head->next) 
        return;
    if (head->next->value == val) {
        delHead();
        return;
    }
    Node* cur = head;
    while (cur->next && cur->next->next && cur->next->next->value != val) {
        cur = cur->next;
    }
    if (!cur->next || !cur->next->next) 
        return;
    Node* tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
}


//текстовая сериализация
void MyList::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) return;

    int count = 0;
    for (Node* curr = head; curr; curr = curr->next) {
        count++;
    }
    file << count << "\n";

    for (Node* curr = head; curr; curr = curr->next) {
        writeStringText(file, curr->value);
    }
}

void MyList::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;

    while (head) delHead();

    int count;
    file >> count;
    string dummy; getline(file, dummy);

    if (file.fail()) return;

    for (int i = 0; i < count; ++i) {
        string val = readStringText(file);
        addTail(val); 
    }
}

//бинарная
void MyList::saveToBinaryFile(const string& filename) const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file) return;

    int count = 0;
    for (Node* curr = head; curr; curr = curr->next) {
        count++;
    }
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (Node* curr = head; curr; curr = curr->next) {
        writeString(file, curr->value);
    }
}

void MyList::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return;

    while (head) delHead();

    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (file.fail()) return;

    for (int i = 0; i < count; ++i) {
        string val = readString(file);
        if (file.fail()) break;
        addTail(val); 
    }
}