package ds

import (
	"os"
	"testing"
)

func TestMyList_Branch_Deletions(t *testing.T) {
	list := NewMyList()
	list.DelTail() 
	list.AddHead("A")
	list.DelTail() 
	if list.Head != nil {
		t.Errorf("Expected empty list")
	}
	list.AddTail("A")
	list.AddTail("B")
	list.DelTail()
	if list.Head.Value != "A" {
		t.Errorf("Expected A")
	}
	list.DelByValue("Z")
	list.DelByValue("A")
	if list.Head != nil {
		t.Errorf("Expected empty list")
	}
	list.AddTail("X")
	list.AddTail("Y")
	list.DelByValue("Y")
	if list.FindValue("Y") {
		t.Errorf("Y should be deleted")
	}
}

func TestMyList_Branch_AdvancedOps(t *testing.T) {
	list := NewMyList()
	list.DelAfterValue("A")
	list.AddTail("A")
	list.DelAfterValue("A")
	list.AddTail("B")
	list.DelAfterValue("Z")
	list.DelAfterValue("A")
	if list.FindValue("B") {
		t.Errorf("B should be deleted")
	}
	list.DelBeforeValue("A")
	list.AddHead("A")
	list.DelBeforeValue("A")

	l2 := NewMyList()
	l2.AddTail("1")
	l2.AddTail("2")
	l2.AddTail("3")
	l2.DelBeforeValue("2")
	if l2.Head.Value != "2" {
		t.Errorf("Expected head 2")
	}

	l3 := NewMyList()
	l3.AddTail("X")
	l3.AddTail("Y")
	l3.AddTail("Z")
	l3.AddTail("W")
	l3.DelBeforeValue("W")
	if l3.FindValue("Z") {
		t.Errorf("Z should be deleted")
	}
	l3.AddAfter("W", "End")
	l3.AddBefore("X", "Start")
	l3.AddAfter("Missing", "No")
	l3.AddBefore("Missing", "No")
	l3.ReadBack()
	
	// Empty list checks
	lEmpty := NewMyList()
	lEmpty.AddBefore("A", "B")
	lEmpty.AddAfter("A", "B")
	lEmpty.ReadBack()
	lEmpty.ReadForward()
}

func TestMyList_SaveAndLoad(t *testing.T) {
	l := NewMyList()
	l.AddTail("A")
	l.AddTail("B")
	filename := "list_test.bin"
	l.SaveToFile(filename)
	defer os.Remove(filename)
	l2 := NewMyList()
	l2.LoadFromFile(filename)
	if !l2.FindValue("A") || !l2.FindValue("B") {
		t.Errorf("List load failed")
	}
}

func TestMyList_Coverage(t *testing.T) {
	l := NewMyList()
	
	l.ReadForward()
	l.ReadBack()
	l.DelHead()
	l.DelTail()
	l.DelByValue("X")
	l.AddBefore("A", "B") 
	l.AddAfter("A", "B")  
	
	l.AddTail("A")
	l.AddBefore("A", "BeforeA") 
	l.DelTail() 
	if !l.FindValue("BeforeA") { t.Error("Expected BeforeA") }
	
	l.DelHead() 
	if l.Head != nil { t.Error("Should be empty") }

	l.AddHead("1")
	l.AddTail("2")
	l.AddTail("3")
	
	l.AddAfter("1", "1.5")
	l.AddAfter("3", "3.5") 
	l.AddAfter("99", "XX") 

	l.AddBefore("3", "2.5")
	l.AddBefore("1", "0.5") 
	l.AddBefore("99", "XX") 

	l.DelByValue("1")   
	l.DelByValue("0.5") 
	l.DelByValue("3.5") 
	l.DelByValue("99")  

	l2 := NewMyList()
	l2.DelAfterValue("X") 
	l2.DelBeforeValue("X") 
	
	l2.AddTail("A")
	l2.DelAfterValue("A") 
	l2.DelBeforeValue("A") 
	
	l2.AddTail("B") 
	l2.DelBeforeValue("B") 
	if l2.Head.Value != "B" { t.Error("DelBefore failed") }
	
	l2.AddTail("C") 
	l2.DelAfterValue("B") 
	if l2.FindValue("C") { t.Error("DelAfter failed") }

	l2.ReadBack()

	l2.SaveToFile("list_cov.txt")
	defer os.Remove("list_cov.txt")
	l3 := NewMyList()
	l3.LoadFromFile("list_cov.txt")
	if l3.Head.Value != "B" { t.Error("Load failed") }

	l2.SaveToBinaryFile("list_cov.bin")
	defer os.Remove("list_cov.bin")
	l4 := NewMyList()
	l4.LoadFromBinaryFile("list_cov.bin")
	if l4.Head.Value != "B" { t.Error("Bin Load failed") }
}