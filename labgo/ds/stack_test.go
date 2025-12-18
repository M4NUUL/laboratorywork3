package ds

import (
	"os"
	"testing"
)

func TestStack_Branch_Coverage(t *testing.T) {
	s := NewStack()
	if !s.IsEmpty() {
		t.Errorf("New stack should be empty")
	}
	if s.Pop() != "[STACK_EMPTY]" {
		t.Errorf("Expected empty")
	}
	if s.Peek() != "[STACK_EMPTY]" {
		t.Errorf("Expected empty")
	}
	s.ReadStack() // Empty print

	s.Push("A")
	if s.Peek() != "A" {
		t.Errorf("Expected A")
	}
	if s.Pop() != "A" {
		t.Errorf("Expected A")
	}
	s.ReadStack()
}

func TestStack_SaveAndLoad(t *testing.T) {
	s := NewStack()
	s.Push("hello")
	s.Push("world")
	s.SaveToFile("stack_test.dat")
	defer os.Remove("stack_test.dat")

	s2 := NewStack()
	s2.LoadFromFile("stack_test.dat")
	if s2.Pop() != "world" {
		t.Errorf("Expected world")
	}
	if s2.Pop() != "hello" {
		t.Errorf("Expected hello")
	}
}

func TestStack_Coverage(t *testing.T) {
	s := NewStack()
	
	if !s.IsEmpty() { t.Error("New stack not empty") }
	if s.Pop() != "[STACK_EMPTY]" { t.Error("Pop empty failed") }
	if s.Peek() != "[STACK_EMPTY]" { t.Error("Peek empty failed") }
	s.ReadStack() 

	s.Push("A")
	s.Push("B")
	if s.Peek() != "B" { t.Error("Peek failed") }
	s.ReadStack() 

	if s.Pop() != "B" { t.Error("Pop failed") }
	if s.Pop() != "A" { t.Error("Pop 2 failed") }
	if !s.IsEmpty() { t.Error("Should be empty") }

	s.Push("Bottom")
	s.Push("Top")
	
	s.SaveToFile("st.txt")
	defer os.Remove("st.txt")
	
	s2 := NewStack()
	s2.LoadFromFile("st.txt")
	if s2.Pop() != "Top" { t.Error("Order lost in Text Save/Load") }
	
	s.SaveToBinaryFile("st.bin")
	defer os.Remove("st.bin")
	
	s3 := NewStack()
	s3.LoadFromBinaryFile("st.bin")
	if s3.Pop() != "Top" { t.Error("Order lost in Bin Save/Load") }
}