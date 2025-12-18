package ds

import (
	"fmt"
)


type ListNode struct {
	Value string
	Next  *ListNode
}

type MyList struct {
	Head *ListNode
}

func NewMyList() *MyList {
	return &MyList{}
}

func (l *MyList) AddHead(val string) {
	l.Head = &ListNode{Value: val, Next: l.Head}
}

func (l *MyList) AddTail(val string) {
	newNode := &ListNode{Value: val}
	if l.Head == nil {
		l.Head = newNode
		return
	}
	cur := l.Head
	for cur.Next != nil {
		cur = cur.Next
	}
	cur.Next = newNode
}

func (l *MyList) AddBefore(target, val string) {
	if l.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	if l.Head.Value == target {
		l.AddHead(val)
		return
	}
	cur := l.Head
	for cur.Next != nil && cur.Next.Value != target {
		cur = cur.Next
	}
	if cur.Next == nil {
		fmt.Println("Элемент не найден")
		return
	}
	newNode := &ListNode{Value: val, Next: cur.Next}
	cur.Next = newNode
}

func (l *MyList) AddAfter(target, val string) {
	if l.Head == nil {
		fmt.Println("Список пуст")
		return
	}
	cur := l.Head
	for cur != nil && cur.Value != target {
		cur = cur.Next
	}
	if cur == nil {
		fmt.Println("Элемент не найден")
		return
	}
	newNode := &ListNode{Value: val, Next: cur.Next}
	cur.Next = newNode
}

func (l *MyList) DelHead() {
	if l.Head == nil {
		return
	}
	l.Head = l.Head.Next
}

func (l *MyList) DelTail() {
	if l.Head == nil {
		fmt.Println("Список пуст")
		return
	}
	if l.Head.Next == nil {
		l.Head = nil
		return
	}
	cur := l.Head
	for cur.Next.Next != nil {
		cur = cur.Next
	}
	cur.Next = nil
}

func (l *MyList) DelByValue(val string) {
	if l.Head == nil {
		fmt.Println("Список пуст.")
		return
	}
	if l.Head.Value == val {
		l.DelHead()
		fmt.Printf("Элемент %s удален.\n", val)
		return
	}
	cur := l.Head
	for cur.Next != nil && cur.Next.Value != val {
		cur = cur.Next
	}
	if cur.Next == nil {
		fmt.Printf("Элемент %s не найден.\n", val)
		return
	}
	cur.Next = cur.Next.Next
	fmt.Printf("Элемент %s удален.\n", val)
}

func (l *MyList) DelAfterValue(val string) {
	if l.Head == nil || l.Head.Next == nil {
		return
	}
	cur := l.Head
	for cur != nil && cur.Value != val {
		cur = cur.Next
	}
	if cur == nil || cur.Next == nil {
		return
	}
	cur.Next = cur.Next.Next
}

func (l *MyList) DelBeforeValue(val string) {
	if l.Head == nil || l.Head.Next == nil {
		return
	}
	if l.Head.Next.Value == val {
		l.DelHead()
		return
	}
	cur := l.Head
	for cur.Next != nil && cur.Next.Next != nil && cur.Next.Next.Value != val {
		cur = cur.Next
	}
	if cur.Next == nil || cur.Next.Next == nil {
		return
	}
	cur.Next = cur.Next.Next
}

func (l *MyList) FindValue(val string) bool {
	cur := l.Head
	for cur != nil {
		if cur.Value == val {
			return true
		}
		cur = cur.Next
	}
	return false
}

func (l *MyList) ReadForward() {
	if l.Head == nil {
		fmt.Println("Список пуст")
		return
	}
	fmt.Print("Список вперёд: ")
	for cur := l.Head; cur != nil; cur = cur.Next {
		fmt.Printf("\"%s\" ", cur.Value)
	}
	fmt.Println()
}

func (l *MyList) printBackRec(node *ListNode) {
	if node == nil {
		return
	}
	l.printBackRec(node.Next)
	fmt.Printf("\"%s\" ", node.Value)
}

func (l *MyList) ReadBack() {
	if l.Head == nil {
		fmt.Println("Список пуст")
		return
	}
	fmt.Print("Список (назад): ")
	l.printBackRec(l.Head)
	fmt.Println()
}

func (l *MyList) SaveToFile(filename string) error {
    return SaveStringsText(filename, l.toSlice())
}

func (l *MyList) toSlice() []string {
    out := []string{}
    for cur := l.Head; cur != nil; cur = cur.Next {
        out = append(out, cur.Value)
    }
    return out
}


func (l *MyList) LoadFromFile(filename string) error {
    vals, err := LoadStringsText(filename)
    if err != nil { return err }
    l.Head = nil
    for _, v := range vals {
        l.AddTail(v)
    }
    return nil
}

func (l *MyList) SaveToBinaryFile(filename string) error {
    return SaveStringsBinary(filename, l.toSlice())
}

func (l *MyList) LoadFromBinaryFile(filename string) error {
    vals, err := LoadStringsBinary(filename)
    if err != nil { return err }
    l.Head = nil
    for _, v := range vals {
        l.AddTail(v)
    }
    return nil
}
