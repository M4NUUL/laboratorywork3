#include "arr.h"
#include "serialize.h"

using namespace std; 

// Конструктор (
MyArr::MyArr() : data(nullptr), size(0), capacity(0) {
}

// Деструктор 
MyArr::~MyArr() {
    delete[] data;
}

//проверка и расширение памяти при необходимости
void MyArr::ensureCapacity(int newSize) {
    if (newSize <= capacity) {
        return;
    }

    int newCapacity = (capacity == 0) ? 1 : capacity;
    while (newCapacity < newSize) {
        newCapacity *= 2;
    }

    // modernize-use-auto
    auto* newData = new string[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

//добавление в конец
void MyArr::addEnd(const string& val) {
    ensureCapacity(size + 1);
    data[size++] = val;
}

//добавление по индексу
void MyArr::addAt(int idx, const string& val) {
    if (idx < 0 || idx > size) {
        return;
    }

    ensureCapacity(size + 1);

    //сдвигаем элементы вправо, начиная с конца
    for (int i = size; i > idx; --i) {
        data[i] = data[i - 1];
    }

    data[idx] = val;
    size++;
}

void MyArr::addHead(const string& val) {
    ensureCapacity(size + 1);
    for (int i = size; i > 0; --i) {
        data[i] = data[i - 1];
    }
    data[0] = val;
    ++size;
}

// удаление из начала
void MyArr::delHead() {
    if (size == 0) {
        return;
    }
    for (int i = 0; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;

    // умеренное сжатие, как в delAt
    if (size > 0 && size * 4 <= capacity && capacity > 1) {
        int newCapacity = capacity / 2;
        // modernize-use-auto
        auto* newData = new string[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

// удаление из конца
void MyArr::delEnd() {
    if (size == 0) {
        return;
    }
    --size;

    // такое же сжатие, как в delAt
    if (size > 0 && size * 4 <= capacity && capacity > 1) {
        int newCapacity = capacity / 2;
        // modernize-use-auto
        auto* newData = new string[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

//удаление по индексу
void MyArr::delAt(int idx) {
    if (idx < 0 || idx >= size) {
        return;
    }

    for (int i = idx; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }

    size--;

    //уменьшаем capacity, если слишком много пустого места
    if (size > 0 && size * 4 <= capacity && capacity > 1) {
        int newCapacity = capacity / 2;
        // modernize-use-auto
        auto* newData = new string[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

//замена элемента
void MyArr::repArr(int idx, const string& val) {
    if (idx < 0 || idx >= size) {
        return;
    }
    data[idx] = val;
}

//чтение всех элементов
void MyArr::readArray() const {
    if (size == 0) {
        // performance-avoid-endl
        cout << "Массив пуст.\n";
        return;
    }
    cout << "Содержимое массива (" << size << "/" << capacity << "): ";
    for (int i = 0; i < size; ++i) {
        cout << "\"" << data[i] << "\" ";
    }
    cout << "\n";
}

//получение элемента по индексу
auto MyArr::getAt(int idx) const -> string {
    if (idx >= 0 && idx < size) {
        return data[idx];
    }
    return "[INVALID_INDEX]";
}

//логическая длина массива
auto MyArr::lenArr() const -> int {
    return size;
}


void MyArr::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) return;

    file << size << "\n"; 
    for (int i = 0; i < size; ++i) {
        writeStringText(file, data[i]);
    }
}

void MyArr::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;

    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;

    int newSize;
    file >> newSize;
    string dummy; getline(file, dummy); // consume newline

    if (file.fail()) return;

    ensureCapacity(newSize);
    size = newSize;
    
    for (int i = 0; i < size; ++i) {
        data[i] = readStringText(file);
    }
}

void MyArr::saveToBinaryFile(const string& filename) const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file) {
        return;
    }

    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (int i = 0; i < size; ++i) {
        writeString(file, data[i]);
    }
}

void MyArr::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        return;
    }

    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;

    int newSize;
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    if (file.fail()) {
        return;
    }

    ensureCapacity(newSize); 
    size = newSize; 
    
    for (int i = 0; i < size; ++i) {
        data[i] = readString(file); 
        if (file.fail()) {
            size = i; 
            break;
        }
    }
}