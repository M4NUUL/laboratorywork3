package ds

import "fmt"


type QNode struct {
	Data string
	Next *QNode
}

type Queue struct {
	Front *QNode
	Rear  *QNode
}

func NewQueue() *Queue {
	return &Queue{}
}

func (q *Queue) IsEmpty() bool {
	return q.Front == nil
}

func (q *Queue) Push(val string) {
	newNode := &QNode{Data: val, Next: nil}
	if q.IsEmpty() {
		q.Front = newNode
		q.Rear = newNode
	} else {
		q.Rear.Next = newNode
		q.Rear = newNode
	}
}

func (q *Queue) Pop() string {
	if q.IsEmpty() {
		return "[QUEUE_EMPTY]"
	}
	val := q.Front.Data
	q.Front = q.Front.Next
	if q.Front == nil {
		q.Rear = nil
	}
	return val
}

func (q *Queue) Peek() string {
	if q.IsEmpty() {
		return "[QUEUE_EMPTY]"
	}
	return q.Front.Data
}

func (q *Queue) Print() {
	if q.IsEmpty() {
		fmt.Println("Очередь пуста.")
		return
	}
	fmt.Print("Очередь (начало -> конец): ")
	for cur := q.Front; cur != nil; cur = cur.Next {
		fmt.Printf("\"%s\" ", cur.Data)
	}
	fmt.Println()
}

// toSlice - Вспомогательная функция для сериализации
func (q *Queue) toSlice() []string {
    out := []string{}
    for cur := q.Front; cur != nil; cur = cur.Next {
        out = append(out, cur.Data)
    }
    return out
}


func (q *Queue) SaveToFile(filename string) error {
    return SaveStringsText(filename, q.toSlice())
}

func (q *Queue) LoadFromFile(filename string) error {
    vals, err := LoadStringsText(filename)
    if err != nil { return err }
    q.Front = nil
    q.Rear = nil
    for _, v := range vals {
        q.Push(v)
    }
    return nil
}

func (q *Queue) SaveToBinaryFile(filename string) error {
    return SaveStringsBinary(filename, q.toSlice())
}

func (q *Queue) LoadFromBinaryFile(filename string) error {
    vals, err := LoadStringsBinary(filename)
    if err != nil { return err }
    q.Front = nil
    q.Rear = nil
    for _, v := range vals {
        q.Push(v)
    }
    return nil
}