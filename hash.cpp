#include "hash.h"
#include "serialize.h" 
#include <iostream>
#include <cmath>

using namespace std;

auto hash_str(const string& key, int mod) -> int
{
    long long hashVal = 0; 
    for(char character: key)
    {
        hashVal = (hashVal * 31 + std::abs((int)character)) % mod;
    }
    return (int)hashVal;
}


ChainHash::ChainHash(int buckCount) : table(nullptr), cap(buckCount)
{
    if(cap < 1) cap=1;
    table = new Node*[cap];
    for(int i = 0; i< cap; i++) table[i] = nullptr;
}

ChainHash::~ChainHash()
{
    for(int i=0; i < cap; i++)
    {
        Node* cur = table[i];
        while(cur != nullptr)
        {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
    delete[] table;
    table = nullptr;
    cap = 0;
}

void ChainHash::insert(const string& key, const string& value) {
    int idx = hash_str(key, cap);

    Node* head = table[idx];
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->key == key) {
            cur->val = value;
            return;
        }
        cur = cur->next;
    }

    Node* newNode = new Node(key, value);
    newNode->next = head;
    table[idx] = newNode;
}

auto ChainHash::erase(const string& key) -> bool
{
    int idx = hash_str(key, cap);
    
    Node* cur = table[idx];
    Node* prv = nullptr;

    while(cur != nullptr)
    {
        if(cur->key == key)
        {
            if(prv != nullptr) {
                prv->next = cur->next;
            } else{
                table[idx] = cur->next;
            }
            delete cur;
            return true;
        }
        prv = cur;
        cur = cur->next;
    }
    return false;
}

auto ChainHash::find(const string& key) -> string
{
    int idx = hash_str(key, cap);
    Node* cur = table[idx];

    while (cur != nullptr) {
        if (cur->key == key) {
            return cur->val;
        }
        cur = cur->next;
    }
    return "";
}

void ChainHash::show() {
    cout << "цепочки: ";
    bool any = false;
    for (int i = 0; i < cap; i++) {
        if (table[i] != nullptr) {
            any = true;
            cout << "[" << i << "]" << ": ";
            Node* cur = table[i];
            while (cur != nullptr) {
                cout << cur->key << "->" << cur->val;
                if (cur->next != nullptr) cout << " -> ";
                cur = cur->next;
            }
            cout << "  ";
        }
    }
    if (!any) cout << "пусто";
    cout << "\n";
}

void ChainHash::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) return;

    file << cap << "\n"; 

    // Считаем количество элементов
    int count = 0;
    for (int i = 0; i < cap; ++i) {
        Node* curr = table[i];
        while (curr) {
            count++;
            curr = curr->next;
        }
    }
    file << count << "\n";

    // Записываем данные
    for (int i = 0; i < cap; ++i) {
        Node* curr = table[i];
        while (curr) {
            writeStringText(file, curr->key);
            writeStringText(file, curr->val);
            curr = curr->next;
        }
    }
}

void ChainHash::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;

    // Очистка текущей таблицы
    for(int i=0; i < cap; i++) {
        Node* cur = table[i];
        while(cur != nullptr) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
    delete[] table;

    // Чтение новой
    int newCap;
    file >> newCap;
    string dummy; getline(file, dummy); 
    cap = newCap;
    table = new Node*[cap];
    for(int i = 0; i < cap; i++) table[i] = nullptr;

    int count;
    file >> count;
    getline(file, dummy);

    if (file.fail()) return;
    for (int i = 0; i < count; ++i) {
        string key = readStringText(file);
        string val = readStringText(file);
        if (file.fail()) break;
        insert(key, val);
    }
}

void ChainHash::saveToBinaryFile(const string& filename) const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file) return;
    
    file.write(reinterpret_cast<const char*>(&cap), sizeof(cap));
    
    int count = 0;
    for (int i = 0; i < cap; ++i) {
        Node* curr = table[i];
        while (curr) {
            count++;
            curr = curr->next;
        }
    }
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (int i = 0; i < cap; ++i) {
        Node* curr = table[i];
        while (curr) {
            writeString(file, curr->key);
            writeString(file, curr->val);
            curr = curr->next;
        }
    }
}

void ChainHash::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return;
    
    // Очистка
    for(int i=0; i < cap; i++) {
        Node* cur = table[i];
        while(cur != nullptr) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
    delete[] table;
    
    file.read(reinterpret_cast<char*>(&cap), sizeof(cap));
    table = new Node*[cap];
    for(int i = 0; i < cap; i++) table[i] = nullptr;
    
    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    if (file.fail()) return;
    for (int i = 0; i < count; ++i) {
        string key = readString(file);
        string val = readString(file);
        if (file.fail()) break;
        insert(key, val);
    }
}


OpenHash::OpenHash(int size) : table(nullptr), cap(size)
{
    if(cap < 1) cap=1;
    table = new Entry[cap];
    for (int i = 0; i < cap; ++i) {
        table[i].used    = false;
        table[i].deleted = false;
    }
}

OpenHash::~OpenHash()
{
    delete[] table;
    table = nullptr;
    cap = 0;
}

void OpenHash::insert(const string& key, const string& value)
{
    int idx = hash_str(key, cap);
    int start = idx;
    
    while(true)
    {
        if(!table[idx].used && !table[idx].deleted) 
        {
            table[idx].key = key;
            table[idx].val = value;
            table[idx].used = true;
            table[idx].deleted = false;
            return;
        }
        if (table[idx].used && table[idx].key == key) {
            table[idx].val = value;
            return;
        }
        if (table[idx].deleted) {
            table[idx].key     = key;
            table[idx].val     = value;
            table[idx].used    = true;
            table[idx].deleted = false;
            return;
        }

        idx = (idx+1) % cap;
        
        if(idx == start)
        {
            cout << "Таблица переполнена" << "\n";
            return;
        }
    }
}

auto OpenHash::erase(const string& key) -> bool
{
    int idx = hash_str(key, cap);
    int start = idx;

    while(true)
    {
        if (table[idx].used && table[idx].key == key) {
            table[idx].used    = false;
            table[idx].deleted = true;
            return true;
        }
        if (!table[idx].used && !table[idx].deleted) {
            return false;
        }
        idx = (idx + 1) % cap;

        if (idx == start) {
            return false;
        }
    }
}

auto OpenHash::find(const string& key) const -> string {
    int idx   = hash_str(key, cap);
    int start = idx;

    while (true) {
        if (table[idx].used && table[idx].key == key) {
            return table[idx].val;
        }
        if (!table[idx].used && !table[idx].deleted) {
            return "";
        }
        idx = (idx + 1) % cap;
        if (idx == start) {
            return "";
        }
    }
}

void OpenHash::show() {
    cout << "ОТКР.АДР: ";
    bool any = false;
    for (int i = 0; i < cap; i++) {
        if (table[i].used) {
            any = true;
            cout << "[" << i << "]" << table[i].key << "->" << table[i].val << "  ";
        } else if (table[i].deleted) {
            any = true;
            cout << "[" << i << "]" << "(удалено)  ";
        }
    }
    if (!any) cout << "пусто";
    cout << "\n";
}

void OpenHash::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) return;
    
    file << cap << "\n";

    int count = 0;
    for (int i = 0; i < cap; ++i) {
        if (table[i].used) count++;
    }
    file << count << "\n";

    for (int i = 0; i < cap; ++i) {
        if (table[i].used) {
            writeStringText(file, table[i].key);
            writeStringText(file, table[i].val);
        }
    }
}

void OpenHash::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;

    delete[] table;
    
    int newCap;
    file >> newCap;
    string dummy; getline(file, dummy);
    
    cap = newCap;
    table = new Entry[cap];
    
    int count;
    file >> count;
    getline(file, dummy);

    if (file.fail()) return;
    for (int i = 0; i < count; ++i) {
        string key = readStringText(file);
        string val = readStringText(file);
        if (file.fail()) break;
        insert(key, val);
    }
}

//бинар сериализац
void OpenHash::saveToBinaryFile(const string& filename) const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file) return;
    file.write(reinterpret_cast<const char*>(&cap), sizeof(cap));
    int count = 0;
    for (int i = 0; i < cap; ++i) {
        if (table[i].used) count++;
    }
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (int i = 0; i < cap; ++i) {
        if (table[i].used) {
            writeString(file, table[i].key);
            writeString(file, table[i].val);
        }
    }
}

void OpenHash::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return;
    delete[] table;
    file.read(reinterpret_cast<char*>(&cap), sizeof(cap));
    table = new Entry[cap];
    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (file.fail()) return;
    for (int i = 0; i < count; ++i) {
        string key = readString(file);
        string val = readString(file);
        if (file.fail()) break;
        insert(key, val);
    }
}

auto is_space_char(char charToCheck) -> bool {
    return charToCheck == ' ' || charToCheck == '\t';
}

void parse_cmd(const string& line, string& cmd, string& arg1, string& rest) {
    cmd.clear(); arg1.clear(); rest.clear();
    int lineLength = (int)line.size();
    int idx = 0;
    
    while (idx < lineLength && is_space_char(line[idx])) { idx++; }

    while (idx < lineLength && !is_space_char(line[idx])) {
        cmd.push_back(line[idx]); idx++;
    }
    while (idx < lineLength && is_space_char(line[idx])) { idx++; }
    while (idx < lineLength && !is_space_char(line[idx])) {
        arg1.push_back(line[idx]); idx++;
    }
    while (idx < lineLength && is_space_char(line[idx])) { idx++; }
    if (idx < lineLength) rest = line.substr(idx);
}

void hash_man() {
    cout << "УПРАВЛЕНИЕ ХЕШ-ТАБЛИЦАМИ" << "\n";
    ChainHash htChain(10);
    OpenHash  htOpen(10);

    while (true) {
        cout << "\n";
        cout << "Команды: INSERT k v | DELETE k | SEARCH k | SHOW | BACK" << "\n";
        cout << "Введите команду: ";
        string line;
        if (!getline(cin, line)) { break; }
        string cmd, arg1, rest;
        parse_cmd(line, cmd, arg1, rest);

        if (cmd.empty()) continue;
        if (cmd == "BACK") {
            cout << "Выход" << endl;
            break;
        }
        if (cmd == "SHOW") {
            htChain.show();
            htOpen.show();
            continue;
        }
        if (cmd == "INSERT") {
            htChain.insert(arg1, rest);
            htOpen.insert(arg1, rest);
            continue;
        }
        if (cmd == "DELETE") {
            htChain.erase(arg1);
            htOpen.erase(arg1);
            continue;
        }
        if (cmd == "SEARCH") {
            string v1 = htChain.find(arg1);
            string v2 = htOpen.find(arg1);
            cout << "Chain: " << (v1.empty() ? "Not found" : v1) << "\n";
            cout << "Open:  " << (v2.empty() ? "Not found" : v2) << "\n";
            continue;
        }
    }
}