package ds

import (

	"fmt"
)

type DNode struct {
	Value string
	Next  *DNode
	Prev  *DNode
}

type DList struct {
	Head *DNode
	Tail *DNode
}

func NewDList() *DList {
	return &DList{}
}

func (d *DList) AddHead(val string) {
	node := &DNode{Value: val, Next: d.Head, Prev: nil}
	if d.Head != nil {
		d.Head.Prev = node
	} else {
		d.Tail = node
	}
	d.Head = node
}

func (d *DList) AddTail(val string) {
	node := &DNode{Value: val, Next: nil, Prev: d.Tail}
	if d.Tail != nil {
		d.Tail.Next = node
	} else {
		d.Head = node
	}
	d.Tail = node
}

func (d *DList) AddBefore(target, val string) {
	if d.Head == nil {
		return
	}
	for cur := d.Head; cur != nil; cur = cur.Next {
		if cur.Value == target {
			node := &DNode{Value: val, Next: cur, Prev: cur.Prev}
			if cur.Prev != nil {
				cur.Prev.Next = node
			} else {
				d.Head = node
			}
			cur.Prev = node
			return
		}
	}
}

func (d *DList) AddAfter(target, val string) {
	if d.Head == nil {
		return
	}
	for cur := d.Head; cur != nil; cur = cur.Next {
		if cur.Value == target {
			node := &DNode{Value: val, Next: cur.Next, Prev: cur}
			if cur.Next != nil {
				cur.Next.Prev = node
			} else {
				d.Tail = node
			}
			cur.Next = node
			return
		}
	}
}

func (d *DList) DelHead() {
	if d.Head == nil {
		return
	}
	d.Head = d.Head.Next
	if d.Head != nil {
		d.Head.Prev = nil
	} else {
		d.Tail = nil
	}
}

func (d *DList) DelTail() {
	if d.Tail == nil {
		return
	}
	d.Tail = d.Tail.Prev
	if d.Tail != nil {
		d.Tail.Next = nil
	} else {
		d.Head = nil
	}
}

func (d *DList) findNode(val string) *DNode {
	for cur := d.Head; cur != nil; cur = cur.Next {
		if cur.Value == val {
			return cur
		}
	}
	return nil
}

func (d *DList) DelByVal(val string) {
	cur := d.findNode(val)
	if cur == nil {
		return
	}
	if cur.Prev != nil {
		cur.Prev.Next = cur.Next
	} else {
		d.Head = cur.Next
	}
	if cur.Next != nil {
		cur.Next.Prev = cur.Prev
	} else {
		d.Tail = cur.Prev
	}
}

func (d *DList) Contains(val string) bool {
	return d.findNode(val) != nil
}

func (d *DList) ReadForward() {
	if d.Head == nil {
		fmt.Println("Список пуст")
		return
	}
	fmt.Print("Список вперед: ")
	for cur := d.Head; cur != nil; cur = cur.Next {
		fmt.Printf(" %s ", cur.Value)
	}
	fmt.Println()
}

func (d *DList) ReadBackward() {
	if d.Tail == nil {
		fmt.Println("Список пуст")
		return
	}
	fmt.Print("Список назад: ")
	for cur := d.Tail; cur != nil; cur = cur.Prev {
		fmt.Printf("\"%s\" ", cur.Value)
	}
	fmt.Println()
}

func (d *DList) DelAfterValue(val string) {
	targetNode := d.findNode(val)
	if targetNode == nil || targetNode.Next == nil {
		return
	}
	d.DelByVal(targetNode.Next.Value)
}

func (d *DList) DelBeforeValue(val string) {
	targetNode := d.findNode(val)
	if targetNode == nil || targetNode.Prev == nil {
		return
	}
	d.DelByVal(targetNode.Prev.Value)
}

func (d *DList) toSlice() []string {
	out := []string{}
	for cur := d.Head; cur != nil; cur = cur.Next {
		out = append(out, cur.Value)
	}
	return out
}


func (d *DList) SaveToFile(filename string) error {
    return SaveStringsText(filename, d.toSlice())
}

func (d *DList) LoadFromFile(filename string) error {
    vals, err := LoadStringsText(filename)
    if err != nil { return err }
    d.Head = nil
    d.Tail = nil
    for _, v := range vals {
        d.AddTail(v)
    }
    return nil
}

func (d *DList) SaveToBinaryFile(filename string) error {
    return SaveStringsBinary(filename, d.toSlice())
}

func (d *DList) LoadFromBinaryFile(filename string) error {
    vals, err := LoadStringsBinary(filename)
    if err != nil { return err }
    d.Head = nil
    d.Tail = nil
    for _, v := range vals {
        d.AddTail(v)
    }
    return nil
}
