package ds

import (
    "bufio"
    "fmt"
    "os"
)


type SNode struct {
	Value string
	Next  *SNode
}

type Stack struct {
	Top *SNode
}

func NewStack() *Stack {
	return &Stack{}
}

func (s *Stack) Push(val string) {
	s.Top = &SNode{Value: val, Next: s.Top}
}

func (s *Stack) Pop() string {
	if s.Top == nil {
		return "[STACK_EMPTY]"
	}
	val := s.Top.Value
	s.Top = s.Top.Next
	return val
}

func (s *Stack) Peek() string {
	if s.Top == nil {
		return "[STACK_EMPTY]"
	}
	return s.Top.Value
}

func (s *Stack) IsEmpty() bool {
	return s.Top == nil
}

func (s *Stack) ReadStack() {
	if s.Top == nil {
		fmt.Println("Стек пуст")
		return
	}
	fmt.Println("Содержимое стека (сверху вниз): ")
	for cur := s.Top; cur != nil; cur = cur.Next {
		fmt.Printf("  %s\n", cur.Value)
	}
}

func (s *Stack) toSlice() []string {
    out := []string{}
    for cur := s.Top; cur != nil; cur = cur.Next {
        out = append(out, cur.Value)
    }
    return out
}


func (s *Stack) SaveToFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	arr := s.toSlice()
	fmt.Fprintln(file, len(arr))
	// Сохраняем снизу вверх (reverse), чтобы при Load Push восстановил порядок
	for i := len(arr) - 1; i >= 0; i-- {
		WriteStringText(file, arr[i])
	}
	return nil
}

func (s *Stack) LoadFromFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil { return err }
	defer file.Close()
	s.Top = nil
	scanner := bufio.NewScanner(file)

	var count int
	if scanner.Scan() { fmt.Sscanf(scanner.Text(), "%d", &count) }

	for i := 0; i < count; i++ {
		val := ReadStringText(scanner)
		s.Push(val)
	}
	return nil
}

// --- БИНАРНАЯ ---
func (s *Stack) SaveToBinaryFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	arr := s.toSlice()
	if err := WriteInt32(file, int32(len(arr))); err != nil { return err }

	for i := len(arr) - 1; i >= 0; i-- {
		if err := WriteString(file, arr[i]); err != nil { return err }
	}
	return nil
}

func (s *Stack) LoadFromBinaryFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil { return err }
	defer file.Close()
	s.Top = nil

	count, err := ReadInt32(file)
	if err != nil { return err }

	for i := 0; i < int(count); i++ {
		val, err := ReadString(file)
		if err != nil { return err }
		s.Push(val)
	}
	return nil
}