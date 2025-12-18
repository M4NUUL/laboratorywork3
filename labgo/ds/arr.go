package ds

import "fmt"


// MyArr - динамический массив строк
type MyArr struct {
	data []string
}

// NewMyArr создает новый массив
func NewMyArr() *MyArr {
	return &MyArr{
		data: make([]string, 0),
	}
}

// AddEnd добавляет элемент в конец
func (a *MyArr) AddEnd(val string) {
	a.data = append(a.data, val)
}

// AddHead добавляет элемент в начало
func (a *MyArr) AddHead(val string) {
	a.data = append([]string{val}, a.data...)
}

// AddAt добавляет элемент по индексу
func (a *MyArr) AddAt(idx int, val string) {
	if idx < 0 || idx > len(a.data) {
		return
	}
	if idx == len(a.data) {
		a.AddEnd(val)
		return
	}
	a.data = append(a.data[:idx+1], a.data[idx:]...)
	a.data[idx] = val
}

// DelHead удаляет элемент из начала
func (a *MyArr) DelHead() {
	if len(a.data) == 0 {
		return
	}
	a.data = a.data[1:]
}

// DelEnd удаляет элемент из конца
func (a *MyArr) DelEnd() {
	if len(a.data) == 0 {
		return
	}
	a.data = a.data[:len(a.data)-1]
}

// DelAt удаляет элемент по индексу
func (a *MyArr) DelAt(idx int) {
	if idx < 0 || idx >= len(a.data) {
		return
	}
	a.data = append(a.data[:idx], a.data[idx+1:]...)
}

// RepArr заменяет элемент по индексу
func (a *MyArr) RepArr(idx int, val string) {
	if idx < 0 || idx >= len(a.data) {
		return
	}
	a.data[idx] = val
}

// GetAt возвращает элемент по индексу
func (a *MyArr) GetAt(idx int) string {
	if idx >= 0 && idx < len(a.data) {
		return a.data[idx]
	}
	return "[INVALID_INDEX]"
}

// LenArr возвращает длину массива
func (a *MyArr) LenArr() int {
	return len(a.data)
}

// ReadArray выводит содержимое массива
func (a *MyArr) ReadArray() {
	if len(a.data) == 0 {
		fmt.Println("Массив пуст.")
		return
	}
	fmt.Printf("Содержимое массива (%d/%d): ", len(a.data), cap(a.data))
	for _, val := range a.data {
		fmt.Printf("\"%s\" ", val)
	}
	fmt.Println()
}


func (a *MyArr) SaveToFile(filename string) error {
    return SaveStringsText(filename, a.data)
}

func (a *MyArr) LoadFromFile(filename string) error {
    vals, err := LoadStringsText(filename)
    if err != nil { return err }
    a.data = vals
    return nil
}

func (a *MyArr) SaveToBinaryFile(filename string) error {
    return SaveStringsBinary(filename, a.data)
}

func (a *MyArr) LoadFromBinaryFile(filename string) error {
    vals, err := LoadStringsBinary(filename)
    if err != nil { return err }
    a.data = vals
    return nil
}
