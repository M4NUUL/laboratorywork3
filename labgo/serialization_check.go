package main

import (
	"datastructures/ds"
	"fmt"
	"os"
)

func assert(condition bool, msg string) {
	if !condition {
		fmt.Printf("FAIL: %s\n", msg)
		os.Exit(1)
	}
}

func header(name string) {
	fmt.Printf("\n=== Тестирование %s ===\n", name)
}

func sep() {
	fmt.Println()
}



func testMyArr() {
	header("MyArr (Массив)")

	arr := ds.NewMyArr()
	fmt.Println("Добавляем элементы: Москва, Лондон, Токио, Париж")
	arr.AddEnd("Москва")
	arr.AddEnd("Лондон")
	arr.AddEnd("Токио")
	arr.AddEnd("Париж")

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в myarr.txt (Text)")
	arr.SaveToFile("myarr.txt")

	fmt.Println("Загрузка из файла...")
	loadTxt := ds.NewMyArr()
	loadTxt.LoadFromFile("myarr.txt")

	fmt.Println("Проверка данных...")
	assert(loadTxt.LenArr() == 4, "length mismatch")
	fmt.Printf("  - Индекс 0: %s (Ожидалось: Москва)\n", loadTxt.GetAt(0))
	fmt.Printf("  - Индекс 1: %s (Ожидалось: Лондон)\n", loadTxt.GetAt(1))
	fmt.Printf("  - Индекс 3: %s (Ожидалось: Париж)\n", loadTxt.GetAt(3))
	assert(loadTxt.GetAt(0) == "Москва", "val mismatch")
	assert(loadTxt.GetAt(1) == "Лондон", "val mismatch")
	assert(loadTxt.GetAt(3) == "Париж", "val mismatch")
	fmt.Println("Сериализация (Text): ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сериализация в myarr.bin (Binary)")
	arr.SaveToBinaryFile("myarr.bin")

	fmt.Println("Загрузка из файла...")
	loadBin := ds.NewMyArr()
	loadBin.LoadFromBinaryFile("myarr.bin")

	fmt.Println("Проверка данных...")
	fmt.Printf("  - Индекс 0: %s (Ожидалось: Москва)\n", loadBin.GetAt(0))
	fmt.Printf("  - Индекс 1: %s (Ожидалось: Лондон)\n", loadBin.GetAt(1))
	fmt.Printf("  - Индекс 3: %s (Ожидалось: Париж)\n", loadBin.GetAt(3))
	assert(loadBin.GetAt(0) == "Москва", "val mismatch")
	assert(loadBin.GetAt(1) == "Лондон", "val mismatch")
	assert(loadBin.GetAt(3) == "Париж", "val mismatch")
	fmt.Println("Сериализация (Binary): ПРОЙДЕНА")

	fmt.Println("MyArr: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n")
	os.Remove("myarr.txt")
	os.Remove("myarr.bin")
}

func testMyList() {
	header("MyList (Односвязный список)")

	list := ds.NewMyList()
	fmt.Println("Добавляем в хвост: Берлин, Мадрид, Рим")
	list.AddTail("Берлин")
	list.AddTail("Мадрид")
	list.AddTail("Рим")

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в mylist.txt (Text)")
	list.SaveToFile("mylist.txt")

	fmt.Println("Загрузка из файла...")
	loadTxt := ds.NewMyList()
	loadTxt.LoadFromFile("mylist.txt")

	fmt.Println("Проверка наличия значений...")
	vals := []string{"Берлин", "Мадрид", "Рим"}
	for _, v := range vals {
		assert(loadTxt.FindValue(v), v+" missing")
		fmt.Println("  - Найдено:", v)
	}
	fmt.Println("Сериализация (Text): ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сохранение в mylist.bin (Binary)")
	list.SaveToBinaryFile("mylist.bin")

	fmt.Println("Загрузка из файла...")
	loadBin := ds.NewMyList()
	loadBin.LoadFromBinaryFile("mylist.bin")

	fmt.Println("Проверка наличия значений...")
	for _, v := range vals {
		assert(loadBin.FindValue(v), v+" missing")
		fmt.Println("  - Найдено:", v)
	}
	fmt.Println("Сериализация (Binary): ПРОЙДЕНА")

	fmt.Println("MyList: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n")
	os.Remove("mylist.txt")
	os.Remove("mylist.bin")
}


func testDList() {
	header("DList (Двусвязный список)")

	l := ds.NewDList()
	fmt.Println("Добавляем в хвост: Пекин, Сеул, Бангкок")
	l.AddTail("Пекин")
	l.AddTail("Сеул")
	l.AddTail("Бангкок")

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в dlist.txt (Text)")
	l.SaveToFile("dlist.txt")

	fmt.Println("Загрузка из файла...")
	loadTxt := ds.NewDList()
	loadTxt.LoadFromFile("dlist.txt")

	fmt.Println("Проверка наличия значений...")
	for _, v := range []string{"Пекин", "Сеул", "Бангкок"} {
		assert(loadTxt.Contains(v), v+" missing")
		fmt.Println("  - Найдено:", v)
	}
	fmt.Println("Сериализация (Text): ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сохранение в dlist.bin (Binary)")
	l.SaveToBinaryFile("dlist.bin")

	fmt.Println("Загрузка из файла...")
	loadBin := ds.NewDList()
	loadBin.LoadFromBinaryFile("dlist.bin")

	fmt.Println("Проверка наличия значений...")
	for _, v := range []string{"Пекин", "Сеул", "Бангкок"} {
		assert(loadBin.Contains(v), v+" missing")
		fmt.Println("  - Найдено:", v)
	}
	fmt.Println("Сериализация (Binary): ПРОЙДЕНА")

	fmt.Println("DList: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n")
	os.Remove("dlist.txt")
	os.Remove("dlist.bin")
}



func testStack() {
	header("Stack (Стек)")

	s := ds.NewStack()
	fmt.Println("Push: Осло -> Стокгольм -> Копенгаген (верх)")
	s.Push("Осло")
	s.Push("Стокгольм")
	s.Push("Копенгаген")

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в stack.txt")
	s.SaveToFile("stack.txt")

	fmt.Println("Загрузка из файла...")
	loadTxt := ds.NewStack()
	loadTxt.LoadFromFile("stack.txt")

	fmt.Println("Проверка порядка (LIFO)...")
	expected := []string{"Копенгаген", "Стокгольм", "Осло"}
	for i, exp := range expected {
		v := loadTxt.Pop()
		fmt.Printf("  - Pop %d: %s (Ожидалось: %s)\n", i+1, v, exp)
		assert(v == exp, "order mismatch")
	}
	fmt.Println("Сериализация (Text): ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сохранение в stack.bin")
	s.SaveToBinaryFile("stack.bin")

	fmt.Println("Загрузка из файла...")
	loadBin := ds.NewStack()
	loadBin.LoadFromBinaryFile("stack.bin")

	fmt.Println("Проверка порядка (LIFO)...")
	for i, exp := range expected {
		v := loadBin.Pop()
		fmt.Printf("  - Pop %d: %s (Ожидалось: %s)\n", i+1, v, exp)
		assert(v == exp, "order mismatch")
	}
	fmt.Println("Сериализация (Binary): ПРОЙДЕНА")

	fmt.Println("Stack: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n")
	os.Remove("stack.txt")
	os.Remove("stack.bin")
}

func testQueue() {
	header("Queue (Очередь)")

	q := ds.NewQueue()
	fmt.Println("Push: Дели -> Мумбаи -> Калькутта")
	q.Push("Дели")
	q.Push("Мумбаи")
	q.Push("Калькутта")

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в queue.txt")
	q.SaveToFile("queue.txt")

	fmt.Println("Загрузка из файла...")
	loadTxt := ds.NewQueue()
	loadTxt.LoadFromFile("queue.txt")

	fmt.Println("Проверка порядка (FIFO)...")
	expected := []string{"Дели", "Мумбаи", "Калькутта"}
	for i, exp := range expected {
		v := loadTxt.Pop()
		fmt.Printf("  - Pop %d: %s (Ожидалось: %s)\n", i+1, v, exp)
		assert(v == exp, "order mismatch")
	}
	fmt.Println("Сериализация (Text): ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сохранение в queue.bin")
	q.SaveToBinaryFile("queue.bin")

	fmt.Println("Загрузка из файла...")
	loadBin := ds.NewQueue()
	loadBin.LoadFromBinaryFile("queue.bin")

	fmt.Println("Проверка порядка (FIFO)...")
	for i, exp := range expected {
		v := loadBin.Pop()
		fmt.Printf("  - Pop %d: %s (Ожидалось: %s)\n", i+1, v, exp)
		assert(v == exp, "order mismatch")
	}
	fmt.Println("Сериализация (Binary): ПРОЙДЕНА")

	fmt.Println("Queue: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n")
	os.Remove("queue.txt")
	os.Remove("queue.bin")
}

//
// ──────────────────────────────────────────────────────────────
//   CompleteBinaryTree
// ──────────────────────────────────────────────────────────────
//

func testCBT() {
	header("CompleteBinaryTree (CBT)")

	t := ds.NewCBT()
	fmt.Println("Вставка чисел: 50, 30, 70")
	t.Insert(50)
	t.Insert(30)
	t.Insert(70)

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в cbt.txt")
	t.SaveToFile("cbt.txt")

	fmt.Println("Загрузка из cbt.txt...")
	loadTxt := ds.NewCBT()
	loadTxt.LoadFromFile("cbt.txt")

	fmt.Println("Поиск узлов...")
	vals := []int{50, 30, 70}
	for _, v := range vals {
		assert(loadTxt.Search(v), fmt.Sprint(v, " missing"))
		fmt.Println("  -", v, "найдено")
	}
	fmt.Println("Текстовая сериализация: ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сохранение в cbt.bin")
	t.SaveToBinaryFile("cbt.bin")

	fmt.Println("Загрузка из cbt.bin...")
	loadBin := ds.NewCBT()
	loadBin.LoadFromBinaryFile("cbt.bin")

	fmt.Println("Поиск узлов...")
	for _, v := range vals {
		assert(loadBin.Search(v), fmt.Sprint(v, " missing"))
		fmt.Println("  -", v, "найдено")
	}
	fmt.Println("Бинарная сериализация: ПРОЙДЕНА")

	fmt.Println("CompleteBinaryTree: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n")
	os.Remove("cbt.txt")
	os.Remove("cbt.bin")
}


func testHash() {
	header("HashTables (Хеш-таблицы)")

	// CHAIN HASH
	fmt.Println("ChainHash")
	fmt.Println("Вставка: key1->value1, key2->value2")
	ch := ds.NewChainHash(10)
	ch.Insert("key1", "value1")
	ch.Insert("key2", "value2")

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в chain.txt")
	ch.SaveToFile("chain.txt")

	fmt.Println("Загрузка...")
	loadTxt := ds.NewChainHash(10)
	loadTxt.LoadFromFile("chain.txt")

	fmt.Println("Проверка значений...")
	for _, kv := range []struct{ k, v string }{
		{"key1", "value1"},
		{"key2", "value2"},
	} {
		assert(loadTxt.Find(kv.k) == kv.v, kv.k+" mismatch")
		fmt.Printf("  - %s -> %s\n", kv.k, kv.v)
	}
	fmt.Println("ChainHash Текстовая Сериализация: ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сохранение в chain.bin")
	ch.SaveToBinaryFile("chain.bin")

	fmt.Println("Загрузка...")
	loadBin := ds.NewChainHash(10)
	loadBin.LoadFromBinaryFile("chain.bin")

	fmt.Println("Проверка значений...")
	for _, kv := range []struct{ k, v string }{
		{"key1", "value1"},
		{"key2", "value2"},
	} {
		assert(loadBin.Find(kv.k) == kv.v, kv.k+" mismatch")
		fmt.Printf("  - %s -> %s\n", kv.k, kv.v)
	}
	fmt.Println("ChainHash Бинарная Сериализация: ПРОЙДЕНА")

	//
	// OpenHash
	//
	fmt.Println("\nOpenHash")
	fmt.Println("Вставка: k1->v1, k2->v2")
	oh := ds.NewOpenHash(10)
	oh.Insert("k1", "v1")
	oh.Insert("k2", "v2")

	// TEXT
	sep()
	fmt.Println("Тест текстового формата ---")
	fmt.Println("Сохранение в openhash.txt")
	oh.SaveToFile("openhash.txt")

	fmt.Println("Загрузка...")
	ohTxt := ds.NewOpenHash(10)
	ohTxt.LoadFromFile("openhash.txt")

	fmt.Println("Проверка значений...")
	for _, kv := range []struct{ k, v string }{
		{"k1", "v1"},
		{"k2", "v2"},
	} {
		assert(ohTxt.Find(kv.k) == kv.v, kv.k+" mismatch")
		fmt.Printf("  - %s -> %s\n", kv.k, kv.v)
	}
	fmt.Println("OpenHash Текстовая Сериализация: ПРОЙДЕНА")

	// BINARY
	sep()
	fmt.Println("Тест бинарного формата ---")
	fmt.Println("Сохранение в openhash.bin")
	oh.SaveToBinaryFile("openhash.bin")

	fmt.Println("Загрузка...")
	ohBin := ds.NewOpenHash(10)
	ohBin.LoadFromBinaryFile("openhash.bin")

	fmt.Println("Проверка значений...")
	for _, kv := range []struct{ k, v string }{
		{"k1", "v1"},
		{"k2", "v2"},
	} {
		assert(ohBin.Find(kv.k) == kv.v, kv.k+" mismatch")
		fmt.Printf("  - %s -> %s\n", kv.k, kv.v)
	}
	fmt.Println("OpenHash Бинарная Сериализация: ПРОЙДЕНА")

	fmt.Println("HashTables: ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n")

	os.Remove("chain.txt")
	os.Remove("chain.bin")
	os.Remove("openhash.txt")
	os.Remove("openhash.bin")
}



func main() {
	fmt.Println("ЗАПУСК ТЕСТОВ СЕРИАЛИЗАЦИИ СТРУКТУР ДАННЫХ\n")

	testMyArr()
	testMyList()
	testDList()
	testStack()
	testQueue()
	testCBT()
	testHash()

	fmt.Println("=========================================")
	fmt.Println("ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!")
	fmt.Println("=========================================")
}
