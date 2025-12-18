#include <iostream>
#include <string>
#include <sstream> 
#include <iomanip> 

#include "arr.h"
#include "list.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hash.h"
#include "compl.h" 

using namespace std;

void showComm() {
    cout << "--- ОБЩИЕ КОМАНДЫ ---\n"
         << "PRINT - Показать содержимое всех структур\n"
         << "HELP - Показать это сообщение\n"
         << "EXIT - Выйти из программы\n\n"
         << "--- СОХРАНЕНИЕ/ЗАГРУЗКА ---\n"
         << "SAVE <filename> - Сохранить все структуры в файлы (e.g., file.arr)\n"
         << "LOAD <filename> - Загрузить все структуры из файлов\n\n"
         << "--- МАССИВ (MyArr) ---\n"
         << "M_PUSH_END <val> - Добавить в конец массива\n"
         << "M_PUSH_HEAD <val> - Добавить в начало\n"
         << "M_PUSH_AT <idx> <val> - Добавить по индексу\n"
         << "M_DEL_AT <idx> - Удалить по индексу\n"
         << "M_DEL_HEAD - Удалить из начала\n"
         << "M_DEL_TAIL - Удалить из конца\n"
         << "M_GET_AT <idx> - Получить по индексу\n"
         << "M_REPLACE_AT <idx> <val> - Заменить по индексу\n"
         << "M_LENGTH - Узнать длину массива\n\n"
         << "--- ОДНОСВЯЗНЫЙ СПИСОК (MyList) ---\n"
         << "F_PUSH_HEAD <val> - Добавить в начало\n"
         << "F_PUSH_TAIL <val> - Добавить в конец\n"
         << "F_PUSH_AFTER <target> <val> - Добавить после значения\n"
         << "F_PUSH_BEFORE <target> <val> - Добавить до значения\n"
         << "F_DEL_HEAD - Удалить первый элемент\n"
         << "F_DEL_TAIL - Удалить последний элемент\n"
         << "F_DEL_VAL <val> - Удалить по значению\n"
         << "F_GET_VAL <val> - Найти по значению\n\n"
         << "--- ДВУСВЯЗНЫЙ СПИСОК (DList) ---\n"
         << "L_PUSH_HEAD <val> - Добавить в начало\n"
         << "L_PUSH_TAIL <val> - Добавить в конец\n"
         << "L_PUSH_AFTER <target> <val> - Добавить после значения\n"
         << "L_PUSH_BEFORE <target> <val> - Добавить до значения\n"
         << "L_DEL_HEAD - Удалить первый элемент\n"
         << "L_DEL_TAIL - Удалить последний элемент\n"
         << "L_DEL_VAL <val> - Удалить по значению\n"
         << "L_GET_VAL <val> - Найти по значению\n"
         << "L_PRINT_REV - Печать в обратном порядке\n\n"
         << "--- ОЧЕРЕДЬ (Queue) ---\n"
         << "Q_PUSH <val> - Добавить в очередь\n"
         << "Q_POP - Извлечь из очереди\n"
         << "Q_GET - Прочитать первый элемент\n\n"
         << "--- СТЕК (Stack) ---\n"
         << "S_PUSH <val> - Добавить в стек\n"
         << "S_POP - Извлечь из стека\n"
         << "S_GET - Прочитать верхний элемент\n\n"
         << "--- ПОЛНОЕ БИНАРНОЕ ДЕРЕВО (CompleteBT) ---\n"
         << "CBT_INSERT <num> - Вставить число\n"
         << "CBT_REMOVE <num> - Удалить число\n"
         << "CBT_SEARCH <num> - Найти число\n"
         << "CBT_PRINT - Вывести структуру дерева\n"
         << "CBT_CLEAR - Очистить дерево\n"
         << "CBT_SIZE - Узнать размер\n\n"
         << "--- ХЕШ-ТАБЛИЦА (Hash) ---\n"
         << "HASH - Открыть отдельное меню хеш-таблиц\n"
         << "-----------------------\n";
}

void parseLine(const string& line, string& cmd, string& arg1, string& arg2) {
    cmd.clear(); arg1.clear(); arg2.clear();
    stringstream ss(line);
    ss >> cmd;
    ss >> arg1;
    string temp;
    if (getline(ss, temp)) {
        if (!temp.empty() && temp[0] == ' ') 
            arg2 = temp.substr(1);
        else arg2 = temp;
    }
}

int safe_stoi(const string& s) {
    try {
        return stoi(s);
    } catch (...) {
        cout << "ОШИБКА: Ожидалось число, но получено '" << s << "'" << "\n";
        return -1; 
    }
}


int main() {
    MyArr arr;
    MyList slist; 
    DList dlist;
    Queue queue;
    Stack stack;
    CompleteBinaryTree cbt; 

    string line, cmd, arg1, arg2;
    showComm(); 

    while (true) {
        cout << "\n>> "; 
        if (!getline(cin, line)) break; 
        if (line.empty()) continue;

        parseLine(line, cmd, arg1, arg2);

        if (cmd == "EXIT") {
            cout << "До свидания!" << "\n";
            break;
        }
        if (cmd == "HELP") {
            showComm();
            continue;
        }
        if (cmd == "PRINT") {
            cout << "--- Содержимое структур ---" << "\n";
            cout << setw(10) << left << "Массив:" << " "; arr.readArray();
            cout << setw(10) << left << "Список:" << " "; slist.readForward();
            cout << setw(10) << left << "Дв.Список:" << " "; dlist.readForward();
            cout << setw(10) << left << "Стек:" << " "; stack.readStack();
            cout << setw(10) << left << "Очередь:" << " "; queue.print();
            cout << setw(10) << left << "CBT:" << "\n"; cbt.print(); 
            cout << "---------------------------" << "\n";
            continue;
        }

        if (cmd == "SAVE") {
            if (arg1.empty()) { cout << "Ошибка: нужно имя файла-основы." << "\n"; continue; }
            arr.saveToFile(arg1 + ".arr");
            slist.saveToFile(arg1 + ".list");
            dlist.saveToFile(arg1 + ".dlist");
            stack.saveToFile(arg1 + ".stack");
            queue.saveToFile(arg1 + ".queue");
            cout << "Структуры (кроме CBT) сохранены с базовым именем: " << arg1 << "\n";
            continue;
        }
        if (cmd == "LOAD") {
            if (arg1.empty()) { cout << "Ошибка: нужно имя файла-основы." << "\n"; continue; }
            arr.loadFromFile(arg1 + ".arr");
            slist.loadFromFile(arg1 + ".list");
            dlist.loadFromFile(arg1 + ".dlist");
            stack.loadFromFile(arg1 + ".stack");
            queue.loadFromFile(arg1 + ".queue");
            cout << "Структуры (кроме CBT) загружены с базовым именем: " << arg1 << "\n";
            cmd = "PRINT"; 
        }

        if (cmd == "M_PUSH_END") {
            if (arg1.empty()) { cout << "Ошибка: команда требует значение" << "\n"; continue; }
            arr.addEnd(arg1);
            arr.readArray();
        } else if (cmd == "M_PUSH_HEAD") {
            if (arg1.empty()) { cout << "Ошибка: команда требует значение" << "\n"; continue; }
            arr.addHead(arg1);
            arr.readArray();
        } else if (cmd == "M_PUSH_AT") {
            if (arg1.empty() || arg2.empty()) { cout << "Ошибка: команда требует индекс и значение" << "\n"; continue; }
            arr.addAt(safe_stoi(arg1), arg2);
            arr.readArray();
        } else if (cmd == "M_DEL_AT") {
            if (arg1.empty()) { cout << "Ошибка: команда требует индекс." << "\n"; continue; }
            arr.delAt(safe_stoi(arg1));
            arr.readArray();
        } else if (cmd == "M_DEL_HEAD") {             
            arr.delHead();
            arr.readArray();
        } else if (cmd == "M_DEL_TAIL") {        
            arr.delEnd();
            arr.readArray();
        } else if (cmd == "M_GET_AT") {
            if (arg1.empty()) { cout << "Ошибка: команда требует индекс." << "\n"; continue; }
            cout << "Элемент[" << arg1 << "]: " << arr.getAt(safe_stoi(arg1)) << "\n";
        } else if (cmd == "M_REPLACE_AT") {
            if (arg1.empty() || arg2.empty()) { cout << "Ошибка: команда требует индекс и значение." << "\n"; continue; }
            arr.repArr(safe_stoi(arg1), arg2);
            arr.readArray();
        } else if (cmd == "M_LENGTH") {
            cout << "Длина массива: " << arr.lenArr() << "\n";
        }

        else if (cmd == "F_PUSH_HEAD") { slist.addHead(arg1); slist.readForward(); }
        else if (cmd == "F_PUSH_TAIL") { slist.addTail(arg1); slist.readForward(); }
        else if (cmd == "F_PUSH_AFTER") { slist.addAfter(arg1, arg2); slist.readForward(); }
        else if (cmd == "F_PUSH_BEFORE") { slist.addBefore(arg1, arg2); slist.readForward(); }
        else if (cmd == "F_DEL_HEAD") { slist.delHead(); slist.readForward(); }
        else if (cmd == "F_DEL_TAIL") { slist.delTail(); slist.readForward(); }
        else if (cmd == "F_DEL_VAL") { slist.delByValue(arg1); slist.readForward(); }
        else if (cmd == "F_GET_VAL") {
            if (arg1.empty()) { cout << "Ошибка: команда требует значение." << "\n"; continue; }
            cout << "Элемент \"" << arg1 << "\" найден: " << (slist.findValue(arg1) ? "Да" : "Нет") << "\n";
        }

        else if (cmd == "L_PUSH_HEAD") { dlist.addHead(arg1); dlist.readForward(); }
        else if (cmd == "L_PUSH_TAIL") { dlist.addTail(arg1); dlist.readForward(); }
        else if (cmd == "L_PUSH_AFTER") { dlist.addAfter(arg1, arg2); dlist.readForward(); }
        else if (cmd == "L_PUSH_BEFORE") { dlist.addBefore(arg1, arg2); dlist.readForward(); }
        else if (cmd == "L_DEL_HEAD") { dlist.delHead(); dlist.readForward(); }
        else if (cmd == "L_DEL_TAIL") { dlist.delTail(); dlist.readForward(); }
        else if (cmd == "L_DEL_VAL") { dlist.delByVal(arg1); dlist.readForward(); }
        else if (cmd == "L_GET_VAL") { 
            if (arg1.empty()) { cout << "Ошибка: команда требует значение." << "\n"; continue; }
            cout << "Элемент \"" << arg1 << "\" найден: " << (dlist.contains(arg1) ? "Да" : "Нет") << "\n";
        }
        else if (cmd == "L_PRINT_REV") { dlist.readBackward(); }

        else if (cmd == "Q_PUSH") {
            if (arg1.empty()) { cout << "Ошибка: команда требует значение." << "\n"; continue; }
            queue.push(arg1);
            queue.print();
        } else if (cmd == "Q_POP") {
            cout << "Извлечено: " << queue.pop() << "\n";
            queue.print();
        } else if (cmd == "Q_GET") {
            cout << "Первый: " << queue.peek() << "\n";
        }

        else if (cmd == "S_PUSH") {
            if (arg1.empty()) { cout << "Ошибка: команда требует значение." << "\n"; continue; }
            stack.push(arg1);
            stack.readStack();
        } else if (cmd == "S_POP") {
            cout << "Извлечено: " << stack.pop() << "\n";
            stack.readStack();
        } else if (cmd == "S_GET") {
            cout << "Верхний: " << stack.peek() << "\n";
        }

        else if (cmd == "CBT_INSERT") {
            if (arg1.empty()) { cout << "Ошибка: команда требует число." << "\n"; continue; }
            cbt.insert(safe_stoi(arg1));
        } 
        else if (cmd == "CBT_REMOVE") {
            if (arg1.empty()) { cout << "Ошибка: команда требует число." << "\n"; continue; }
            cbt.remove(safe_stoi(arg1));
        }
        else if (cmd == "CBT_SEARCH") {
            if (arg1.empty()) { cout << "Ошибка: команда требует число." << "\n"; continue; }
            cbt.search(safe_stoi(arg1));
        }
        else if (cmd == "CBT_PRINT") {
            cbt.print();
        }
        else if (cmd == "CBT_CLEAR") {
            cbt.clear();
        }
        else if (cmd == "CBT_SIZE") {
            cout << "Размер CBT: " << cbt.getSize() << "\n";
        }

        else if (cmd == "HASH") {
            cout << "--- Вход в подсистему Хеш-таблиц ---" << "\n";
            hash_man();
            cout << "--- Выход из подсистемы Хеш-таблиц ---" << "\n";
        }

        else if (cmd != "PRINT" && cmd != "SAVE" && cmd != "LOAD") { 
            cout << "Неизвестная команда: '" << cmd << "'. Введите HELP для списка команд." << "\n";
        }
    }

    return 0;
}