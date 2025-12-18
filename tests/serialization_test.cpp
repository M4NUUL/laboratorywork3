#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#include "../arr.h"
#include "../list.h"
#include "../dlist.h"
#include "../stack.h"
#include "../queue.h"
#include "../compl.h"
#include "../hash.h" 

using namespace std;

void testMyArr() {
    cout << "=== Тестирование MyArr (Массив) ===" << endl;
    
    MyArr arr1;
    cout << "Добавляем элементы: Москва, Лондон, Токио, Париж" << endl;
    arr1.addEnd("Москва");
    arr1.addEnd("Лондон");
    arr1.addEnd("Токио");
    arr1.addEnd("Париж");
    
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в myarr.txt (Text)" << endl;
    arr1.saveToFile("myarr.txt"); 
    
    cout << "Загрузка из файла..." << endl;
    MyArr arrText;
    arrText.loadFromFile("myarr.txt");
    
    cout << "Проверка данных..." << endl;
    assert(arrText.lenArr() == 4);
    cout << "  - Индекс 0: " << arrText.getAt(0) << " (Ожидалось: Москва)" << endl;
    assert(arrText.getAt(0) == "Москва");
    cout << "  - Индекс 1: " << arrText.getAt(1) << " (Ожидалось: Лондон)" << endl;
    assert(arrText.getAt(1) == "Лондон");
    cout << "  - Индекс 3: " << arrText.getAt(3) << " (Ожидалось: Париж)" << endl;
    assert(arrText.getAt(3) == "Париж");
    cout << "Сериализация (Text): ПРОЙДЕНА" << endl;

    cout << "\nТест бинарного формата ---" << endl;
    cout << "Сериализация в файл: myarr.bin (Binary)" << endl;
    arr1.saveToBinaryFile("myarr.bin"); 
    
    cout << "Загрузка из файла..." << endl;
    MyArr arrBin;
    arrBin.loadFromBinaryFile("myarr.bin");
    
    cout << "Проверка данных..." << endl;
    assert(arrBin.lenArr() == 4);
    cout << "  - Индекс 0: " << arrBin.getAt(0) << " (Ожидалось: Москва)" << endl;
    assert(arrBin.getAt(0) == "Москва");
    cout << "  - Индекс 1: " << arrBin.getAt(1) << " (Ожидалось: Лондон)" << endl;
    assert(arrBin.getAt(1) == "Лондон");
    cout << "  - Индекс 3: " << arrBin.getAt(3) << " (Ожидалось: Париж)" << endl;
    assert(arrBin.getAt(3) == "Париж");
    cout << "Сериализация (Binary): ПРОЙДЕНА" << endl;
    
    cout << "MyArr: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n" << endl;
}

void testMyList() {
    cout << "=== Тестирование MyList (Односвязный список) ===" << endl;
    
    MyList list1;
    cout << "Добавляем в хвост: Берлин, Мадрид, Рим" << endl;
    list1.addTail("Берлин");
    list1.addTail("Мадрид");
    list1.addTail("Рим");
    
    //ТЕКСТ
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в mylist.txt (Text)" << endl;
    list1.saveToFile("mylist.txt");
    
    cout << "Загрузка из файла..." << endl;
    MyList listText;
    listText.loadFromFile("mylist.txt");
    
    cout << "Проверка наличия значений..." << endl;
    assert(listText.findValue("Берлин"));
    cout << "  - Найдено: Берлин" << endl;
    assert(listText.findValue("Мадрид"));
    cout << "  - Найдено: Мадрид" << endl;
    assert(listText.findValue("Рим"));
    cout << "  - Найдено: Рим" << endl;
    cout << "Сериализация (Text): ПРОЙДЕНА" << endl;

    //бин
    cout << "\nТест бинарного формата ---" << endl;
    cout << "Сериализация в файл: mylist_test.bin (Binary)" << endl;
    list1.saveToBinaryFile("mylist_test.bin");
    
    cout << "Загрузка из файла..." << endl;
    MyList listBin;
    listBin.loadFromBinaryFile("mylist_test.bin");
    
    cout << "Проверка наличия значений..." << endl;
    assert(listBin.findValue("Берлин"));
    cout << "  - Найдено: Берлин" << endl;
    assert(listBin.findValue("Мадрид"));
    cout << "  - Найдено: Мадрид" << endl;
    assert(listBin.findValue("Рим"));
    cout << "  - Найдено: Рим" << endl;
    cout << "Сериализация (Binary): ПРОЙДЕНА" << endl;
    
    cout << "MyList: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n" << endl;
}

void testDList() {
    cout << "=== Тестирование DList (Двусвязный список) ===" << endl;
    
    DList list1;
    cout << "Добавляем в хвост: Пекин, Сеул, Бангкок" << endl;
    list1.addTail("Пекин");
    list1.addTail("Сеул");
    list1.addTail("Бангкок");
    
    //ТЕКС
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в dlist_test.txt (Text)" << endl;
    list1.saveToFile("dlist_test.txt");
    
    cout << "Загрузка из файла..." << endl;
    DList listText;
    listText.loadFromFile("dlist_test.txt");
    
    cout << "Проверка наличия значений..." << endl;
    assert(listText.contains("Пекин"));
    cout << "  - Найдено: Пекин" << endl;
    assert(listText.contains("Сеул"));
    cout << "  - Найдено: Сеул" << endl;
    assert(listText.contains("Бангкок"));
    cout << "  - Найдено: Бангкок" << endl;
    cout << "Сериализация (Text): ПРОЙДЕНА" << endl;

    // BINARY
    cout << "\nТест бинарного формата ---" << endl;
    cout << "Сериализация в файл: dlist_test.bin (Binary)" << endl;
    list1.saveToBinaryFile("dlist_test.bin");
    
    cout << "Загрузка из файла..." << endl;
    DList listBin;
    listBin.loadFromBinaryFile("dlist_test.bin");
    
    cout << "Проверка наличия значений..." << endl;
    assert(listBin.contains("Пекин"));
    cout << "  - Найдено: Пекин" << endl;
    assert(listBin.contains("Сеул"));
    cout << "  - Найдено: Сеул" << endl;
    assert(listBin.contains("Бангкок"));
    cout << "  - Найдено: Бангкок" << endl;
    cout << "Сериализация (Binary): ПРОЙДЕНА" << endl;
    
    cout << "DList: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n" << endl;
}

void testStack() {
    cout << "=== Тестирование Stack (Стек) ===" << endl;
    
    Stack stack1;
    cout << "Push: Осло -> Стокгольм -> Копенгаген (верх)" << endl;
    stack1.push("Осло");
    stack1.push("Стокгольм");
    stack1.push("Копенгаген");
    
    //  ТЕКС
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в stack_test.txt (Text)" << endl;
    stack1.saveToFile("stack_test.txt");
    
    cout << "Загрузка из файла..." << endl;
    Stack stackText;
    stackText.loadFromFile("stack_test.txt");
    
    cout << "Проверка порядка (LIFO)..." << endl;
    string valT1 = stackText.pop();
    cout << "  - Pop 1: " << valT1 << " (Ожидалось: Копенгаген)" << endl;
    assert(valT1 == "Копенгаген");
    string valT2 = stackText.pop();
    cout << "  - Pop 2: " << valT2 << " (Ожидалось: Стокгольм)" << endl;
    assert(valT2 == "Стокгольм");
    string valT3 = stackText.pop();
    cout << "  - Pop 3: " << valT3 << " (Ожидалось: Осло)" << endl;
    assert(valT3 == "Осло");
    cout << "Сериализация (Text): ПРОЙДЕНА" << endl;

    // BIN
    cout << "\nТест бинарного формата ---" << endl;
    cout << "Сериализация в файл: stack_test.bin (Binary)" << endl;
    stack1.saveToBinaryFile("stack_test.bin");
    
    cout << "Загрузка из файла..." << endl;
    Stack stackBin;
    stackBin.loadFromBinaryFile("stack_test.bin");
    
    cout << "Проверка порядка (LIFO)..." << endl;
    string valB1 = stackBin.pop();
    cout << "  - Pop 1: " << valB1 << " (Ожидалось: Копенгаген)" << endl;
    assert(valB1 == "Копенгаген");
    string valB2 = stackBin.pop();
    cout << "  - Pop 2: " << valB2 << " (Ожидалось: Стокгольм)" << endl;
    assert(valB2 == "Стокгольм");
    string valB3 = stackBin.pop();
    cout << "  - Pop 3: " << valB3 << " (Ожидалось: Осло)" << endl;
    assert(valB3 == "Осло");
    cout << "Сериализация (Binary): ПРОЙДЕНА" << endl;
    
    cout << "Stack: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n" << endl;
}

void testQueue() {
    cout << "=== Тестирование Queue (Очередь) ===" << endl;
    
    Queue queue1;
    cout << "Push: Дели -> Мумбаи -> Калькутта" << endl;
    queue1.push("Дели");
    queue1.push("Мумбаи");
    queue1.push("Калькутта");
    
    // ТЕКС
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в queue_test.txt (Text)" << endl;
    queue1.saveToFile("queue_test.txt");
    
    cout << "Загрузка из файла..." << endl;
    Queue queueText;
    queueText.loadFromFile("queue_test.txt");
    
    cout << "Проверка порядка (FIFO)..." << endl;
    string valT1 = queueText.pop();
    cout << "  - Pop 1: " << valT1 << " (Ожидалось: Дели)" << endl;
    assert(valT1 == "Дели");
    string valT2 = queueText.pop();
    cout << "  - Pop 2: " << valT2 << " (Ожидалось: Мумбаи)" << endl;
    assert(valT2 == "Мумбаи");
    string valT3 = queueText.pop();
    cout << "  - Pop 3: " << valT3 << " (Ожидалось: Калькутта)" << endl;
    assert(valT3 == "Калькутта");
    cout << "Сериализация (Text): ПРОЙДЕНА" << endl;

    // бин
    cout << "\nТест бинарного формата ---" << endl;
    cout << "Сериализация в файл: queue_test.bin (Binary)" << endl;
    queue1.saveToBinaryFile("queue_test.bin");
    
    cout << "Загрузка из файла..." << endl;
    Queue queueBin;
    queueBin.loadFromBinaryFile("queue_test.bin");
    
    cout << "Проверка порядка (FIFO)..." << endl;
    string valB1 = queueBin.pop();
    cout << "  - Pop 1: " << valB1 << " (Ожидалось: Дели)" << endl;
    assert(valB1 == "Дели");
    string valB2 = queueBin.pop();
    cout << "  - Pop 2: " << valB2 << " (Ожидалось: Мумбаи)" << endl;
    assert(valB2 == "Мумбаи");
    string valB3 = queueBin.pop();
    cout << "  - Pop 3: " << valB3 << " (Ожидалось: Калькутта)" << endl;
    assert(valB3 == "Калькутта");
    cout << "Сериализация (Binary): ПРОЙДЕНА" << endl;
    
    cout << "Queue: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n" << endl;
}

void testCBT() {
    cout << "=== Тестирование CompleteBinaryTree (CBT) ===" << endl;
    
    CompleteBinaryTree tree1;
    cout << "Вставка чисел: 50, 30, 70" << endl;
    tree1.insert(50);
    tree1.insert(30);
    tree1.insert(70);
    
    //текст
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в cbt.txt (Text)" << endl;
    tree1.saveToFile("cbt.txt"); 
    
    cout << "Загрузка из cbt.txt..." << endl;
    CompleteBinaryTree treeText;
    treeText.loadFromFile("cbt.txt");
    
    cout << " Поиск узлов..." << endl;
    assert(treeText.search(50) == true);
    cout << "  - 50 найдено" << endl;
    assert(treeText.search(30) == true);
    cout << "  - 30 найдено" << endl;
    assert(treeText.search(70) == true);
    cout << "  - 70 найдено" << endl;
    cout << "Текстовая сериализация: ПРОЙДЕНА" << endl;

    // бин
    cout << "\n Тест бинарного формата ---" << endl;
    cout << "Сохранение в cbt.bin (Binary)" << endl;
    tree1.saveToBinaryFile("cbt.bin"); 
    
    cout << "Загрузка из cbt.bin..." << endl;
    CompleteBinaryTree treeBin;
    treeBin.loadFromBinaryFile("cbt.bin");
    
    cout << "Поиск узлов..." << endl;
    assert(treeBin.search(50) == true);
    cout << "  - 50 найдено" << endl;
    assert(treeBin.search(30) == true);
    cout << "  - 30 найдено" << endl;
    assert(treeBin.search(70) == true);
    cout << "  - 70 найдено" << endl;
    cout << "Бинарная сериализация: ПРОЙДЕНА" << endl;
    
    cout << "CompleteBinaryTree: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n" << endl;
}

void testHashTable() {
    cout << "=== Тестирование HashTables (Хеш-таблицы) ===" << endl;
    
    cout << "ChainHash" << endl;
    ChainHash ch1(10);
    cout << "Вставка: key1->value1, key2->value2" << endl;
    ch1.insert("key1", "value1");
    ch1.insert("key2", "value2");
    
    // текст
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в chain.txt" << endl;
    ch1.saveToFile("chain.txt");
    
    ChainHash chText(10);
    chText.loadFromFile("chain.txt");
    
    cout << " Проверка значений..." << endl;
    assert(chText.find("key1") == "value1");
    cout << "  - key1 -> " << chText.find("key1") << endl;
    assert(chText.find("key2") == "value2");
    cout << "  - key2 -> " << chText.find("key2") << endl;
    cout << "ChainHash Текстовая Сериализация: ПРОЙДЕНА" << endl;

    cout << "\nТест бинарного формата ---" << endl;
    cout << "Сохранение в chain.bin" << endl;
    ch1.saveToBinaryFile("chain.bin");
    
    ChainHash chBin(10);
    chBin.loadFromBinaryFile("chain.bin");
    
    cout << " Проверка значений..." << endl;
    assert(chBin.find("key1") == "value1");
    cout << "  - key1 -> " << chBin.find("key1") << endl;
    assert(chBin.find("key2") == "value2");
    cout << "  - key2 -> " << chBin.find("key2") << endl;
    cout << "ChainHash Бинарная Сериализация: ПРОЙДЕНА" << endl;


    cout << "\n[ OpenHash ---" << endl;
    OpenHash oh1(10);
    cout << "Вставка: k1->v1, k2->v2" << endl;
    oh1.insert("k1", "v1");
    oh1.insert("k2", "v2");
    
    cout << "\nТест текстового формата ---" << endl;
    cout << "Сохранение в openhash_test.txt" << endl;
    oh1.saveToFile("openhash_test.txt");
    
    OpenHash ohText(10);
    ohText.loadFromFile("openhash_test.txt");
    
    cout << "Проверка значений..." << endl;
    assert(ohText.find("k1") == "v1");
    cout << "  - k1 -> " << ohText.find("k1") << endl;
    assert(ohText.find("k2") == "v2");
    cout << "  - k2 -> " << ohText.find("k2") << endl;
    cout << "OpenHash Текстовая Сериализация: ПРОЙДЕНА" << endl;

    cout << "\nТест бинарного формата ---" << endl;
    cout << "Сохранение в openhash_test.bin" << endl;
    oh1.saveToBinaryFile("openhash_test.bin");
    
    OpenHash ohBin(10);
    ohBin.loadFromBinaryFile("openhash_test.bin");
    
    cout << "Проверка значений..." << endl;
    assert(ohBin.find("k1") == "v1");
    cout << "  - k1 -> " << ohBin.find("k1") << endl;
    assert(ohBin.find("k2") == "v2");
    cout << "  - k2 -> " << ohBin.find("k2") << endl;
    cout << "OpenHash Бинарная Сериализация: ПРОЙДЕНА" << endl;
    
    cout << "HashTables: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n" << endl;
}

int main() {
    setlocale(LC_ALL, "");

    cout << "ЗАПУСК ТЕСТОВ СЕРИАЛИЗАЦИИ СТРУКТУР ДАННЫХ\n" << endl;
    
    try {
        testMyArr();
        testMyList();
        testDList();
        testStack();
        testQueue();
        testCBT();
        testHashTable(); 
        
        cout << "=========================================" << endl;
        cout << "ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!" << endl;
        cout << "=========================================" << endl;
    } catch (const exception& e) {
        cout << "ОШИБКА: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}