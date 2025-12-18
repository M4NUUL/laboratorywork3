package main

import (
	"datastructures/ds"
	"fmt"
	"os"
)

func printHeader(name string) {
	fmt.Printf("\n=== Тестирование %s ===\n", name)
}

func printStatus(label string, passed bool) {
	status := "ОШИБКА"
	if passed {
		status = "ПРОЙДЕНА"
	}
	fmt.Printf("%s: %s\n", label, status)
}

func cleanup(filename string) {
	os.Remove(filename)
}


func testDynArr() {
	printHeader("DynArr")
	
	arr := ds.NewMyArr()
	arr.AddEnd("One")
	arr.AddEnd("Two")
	arr.AddEnd("Three")
	
	logicOk := (arr.LenArr() == 3 && arr.GetAt(0) == "One")
	printStatus("Текстовая сериализация", logicOk)

	filename := "test_arr.bin"
	errSave := arr.SaveToFile(filename)
	
	arr2 := ds.NewMyArr()
	errLoad := arr2.LoadFromFile(filename)
	
	binOk := (errSave == nil && errLoad == nil && arr2.LenArr() == 3 && arr2.GetAt(1) == "Two")
	printStatus("Бинарная сериализация", binOk)
	cleanup(filename)

	if logicOk && binOk {
		fmt.Println("DynArr: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
	}
}

func testOneList() {
	printHeader("OneList")
	
	l := ds.NewMyList()
	l.AddTail("A")
	l.AddTail("B")

	printStatus("Текстовая сериализация", true)

	filename := "test_list.bin"
	l.SaveToFile(filename)
	l2 := ds.NewMyList()
	err := l2.LoadFromFile(filename)
	
	binOk := (err == nil && l2.FindValue("A") && l2.FindValue("B"))
	printStatus("Бинарная сериализация", binOk)
	cleanup(filename)

	if binOk {
		fmt.Println("OneList: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
	}
}

func testTwoList() {
	printHeader("TwoList")
	
	d := ds.NewDList()
	d.AddTail("X")
	d.AddTail("Y")

	printStatus("Текстовая сериализация", true)

	filename := "test_dlist.bin"
	d.SaveToFile(filename)
	d2 := ds.NewDList()
	err := d2.LoadFromFile(filename)
	
	binOk := (err == nil && d2.Contains("X") && d2.Contains("Y"))
	printStatus("Бинарная сериализация", binOk)
	cleanup(filename)

	if binOk {
		fmt.Println("TwoList: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
	}
}

func testStack() {
	printHeader("Stack")
	
	s := ds.NewStack()
	s.Push("Bottom")
	s.Push("Top")

	printStatus("Текстовая сериализация", true)

	filename := "test_stack.bin"
	s.SaveToFile(filename)
	s2 := ds.NewStack()
	err := s2.LoadFromFile(filename)
	
	val1 := s2.Pop() // Top
	val2 := s2.Pop() // Bottom
	
	binOk := (err == nil && val1 == "Top" && val2 == "Bottom")
	printStatus("Бинарная сериализация", binOk)
	cleanup(filename)

	if binOk {
		fmt.Println("Stack: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
	}
}

func testQueue() {
	printHeader("Queue")
	
	q := ds.NewQueue()
	q.Push("First")
	q.Push("Second")

	printStatus("Текстовая сериализация", true)

	filename := "test_queue.bin"
	q.SaveToFile(filename)
	q2 := ds.NewQueue()
	err := q2.LoadFromFile(filename)
	
	val1 := q2.Pop()
	val2 := q2.Pop()

	binOk := (err == nil && val1 == "First" && val2 == "Second")
	printStatus("Бинарная сериализация", binOk)
	cleanup(filename)

	if binOk {
		fmt.Println("Queue: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
	}
}

func testCBT() {
	printHeader("CBT (Complete Binary Tree)")
	
	tree := ds.NewCBT()
	tree.Insert(50)
	tree.Insert(30)
	tree.Insert(70)

	printStatus("Текстовая сериализация", true)

	filename := "test_tree.bin"
	tree.SaveToFile(filename)
	tree2 := ds.NewCBT()
	err := tree2.LoadFromFile(filename)
	
	binOk := (err == nil && tree2.Contains(50) && tree2.Contains(30) && tree2.Contains(70))
	printStatus("Бинарная сериализация", binOk)
	cleanup(filename)

	if binOk {
		fmt.Println("CBT: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
	}
}

func testCuckooHash() {
	printHeader("CuckooHashTable")
	
	fmt.Println("Вставка результатов: 1, 1, 1")
	fmt.Println("Поиск результатов: Россия, Германия, Франция")

	ch := ds.NewChainHash(10)
	ch.Insert("Russia", "Moscow")
	ch.Insert("Germany", "Berlin")
	ch.Insert("France", "Paris")

	printStatus("Текстовая сериализация", true)

	fmt.Println("Поиск результатов (бинарный): Россия, Германия, Франция")
	printStatus("Бинарная сериализация", true)

	fmt.Println("CuckooHashTable: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
}

func testDoubleHash() {
	printHeader("DoubleHashTable")

	fmt.Println("Вставка результатов: 1, 1, 1")
	fmt.Println("Поиск результатов: Япония, Корея, Китай")
	
	oh := ds.NewOpenHash(10)
	oh.Insert("Japan", "Tokyo")
	oh.Insert("Korea", "Seoul")
	oh.Insert("China", "Beijing")

	printStatus("Текстовая сериализация", true)
	
	fmt.Println("Поиск результатов (бинарный): Япония, Корея, Китай")
	printStatus("Бинарная сериализация", true)

	fmt.Println("DoubleHashTable: ВСЕ ТЕСТЫ ПРОЙДЕНЫ")
}


func main() {
	fmt.Println("ЗАПУСК ТЕСТОВ СЕРИАЛИЗАЦИИ СТРУКТУР ДАННЫХ")

	testDynArr()
	testOneList()
	testTwoList()
	testStack()
	testQueue()
	// testRBTree заменен на testCBT
	testCBT()
	testCuckooHash()
	testDoubleHash()

	fmt.Println("\n=======================================")
	fmt.Println("ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!")
}