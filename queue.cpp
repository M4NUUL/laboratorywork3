#include "queue.h"
#include "serialize.h"

using namespace std; 

//конструктор
Queue::Queue() : front(nullptr), rear(nullptr) {
}

//деструктор
Queue::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

void Queue::push(std::string val) {
    QNode* newNode = new QNode;
    newNode->data = val;
    newNode->next = nullptr;

    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

//удаление элемента из начала очереди
string Queue::pop() {
    if (isEmpty()) {
        return "[QUEUE_EMPTY]";
    }
    QNode* tmp = front;
    string value = tmp->data;

    front = front->next;
    delete tmp;

    if (front == nullptr) {
        rear = nullptr;
    }
    return value;
}

string Queue::peek() const {
    if (isEmpty()) {
        return "[QUEUE_EMPTY]";
    }
    return front->data;
}

void Queue::print() const {
    if (isEmpty()) {
        cout << "Очередь пуста." << endl;
        return;
    }
    cout << "Очередь (начало -> конец): ";
    for (QNode* curr = front; curr; curr = curr->next) {
        cout << "\"" << curr->data << "\" ";
    }
    cout << "\n";
}



void Queue::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) return;

    int count = 0;
    for (QNode* curr = front; curr; curr = curr->next) {
        count++;
    }
    file << count << "\n";

    for (QNode* curr = front; curr; curr = curr->next) {
        writeStringText(file, curr->data);
    }
}

void Queue::loadFromFile(const string& filename) {
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

//бинарный
void Queue::saveToBinaryFile(const string& filename) const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file) return;

    int count = 0;
    for (QNode* curr = front; curr; curr = curr->next) {
        count++;
    }
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (QNode* curr = front; curr; curr = curr->next) {
        writeString(file, curr->data);
    }
}

void Queue::loadFromBinaryFile(const string& filename) {
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