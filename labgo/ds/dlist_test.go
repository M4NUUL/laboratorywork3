package ds

import (
	"os"
	"testing"
)

func TestDList_Branch_AllCases(t *testing.T) {
	dl := NewDList()
	dl.DelHead()
	dl.DelTail()
	dl.ReadForward()
	dl.ReadBackward()
	
	// Empty add checks
	dl.AddBefore("A", "B")
	dl.AddAfter("A", "B")

	dl.AddHead("A")
	dl.DelHead()
	if dl.Head != nil {
		t.Errorf("Expected empty")
	}
	dl.AddTail("B")
	dl.DelTail()
	if dl.Tail != nil {
		t.Errorf("Expected empty tail")
	}
	dl.AddHead("2")
	dl.AddHead("1")
	dl.AddTail("3")
	dl.AddAfter("1", "1.5")
	dl.AddBefore("3", "2.5")
	dl.DelByVal("1")
	dl.DelByVal("3")
	dl.DelByVal("2")
	dl.DelAfterValue("NotExists")
	dl.DelBeforeValue("NotExists")
	dl.AddTail("X")
	dl.AddTail("Y")
	dl.DelAfterValue("X")
	dl.DelBeforeValue("X")
	if !dl.Contains("X") {
		t.Errorf("Should contain X")
	}
}

func TestDList_SaveAndLoad(t *testing.T) {
	dl := NewDList()
	dl.AddTail("X")
	dl.AddTail("Y")
	filename := "dlist_test.bin"
	dl.SaveToFile(filename)
	defer os.Remove(filename)
	dl2 := NewDList()
	dl2.LoadFromFile(filename)
	if !dl2.Contains("X") || !dl2.Contains("Y") {
		t.Errorf("DList load failed")
	}
}

func TestDList_FullCoverage(t *testing.T) {
	dl := NewDList()

	dl.ReadForward()
	dl.ReadBackward()
	dl.DelHead()
	dl.DelTail()
	dl.DelByVal("X")
	dl.AddBefore("A", "B")
	dl.AddAfter("A", "B")

	dl.AddHead("A") 
	dl.AddBefore("A", "Pre") 
	dl.DelHead() 
	dl.AddAfter("A", "Post") 
	dl.DelTail() 
	
	dl.AddTail("B") 
	dl.AddTail("C") 
	
	dl.DelByVal("B") 
	if dl.Contains("B") { t.Error("B not deleted") }
	
	dl.DelByVal("A") 
	if dl.Head.Value != "C" { t.Error("Head update failed") }
	
	dl.DelByVal("C") 
	if dl.Head != nil { t.Error("List should be empty") }

	dl.AddTail("1")
	dl.AddTail("2")
	dl.DelAfterValue("1") 
	if dl.Contains("2") { t.Error("DelAfter failed") }
	
	dl.AddTail("3") 
	dl.DelBeforeValue("3") 
	if dl.Contains("1") { t.Error("DelBefore failed") }

	dl.AddTail("X")
	dl.SaveToFile("dl.txt")
	defer os.Remove("dl.txt")
	dl2 := NewDList()
	dl2.LoadFromFile("dl.txt")
	
	dl.SaveToBinaryFile("dl.bin")
	defer os.Remove("dl.bin")
	dl3 := NewDList()
	dl3.LoadFromBinaryFile("dl.bin")
	if !dl3.Contains("X") { t.Error("Bin load failed") }
}