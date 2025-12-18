package ds

import (
	"os"
	"testing"
)

func TestMyArr_Branch_CapacityAndShrink(t *testing.T) {
	arr := NewMyArr()
	for i := 0; i < 65; i++ {
		arr.AddEnd("x")
	}
	if arr.LenArr() < 65 {
		t.Errorf("Expected size >= 65, got %d", arr.LenArr())
	}
	startSize := arr.LenArr()
	for i := 0; i < startSize; i++ {
		arr.DelEnd()
	}
	if arr.LenArr() != 0 {
		t.Errorf("Expected empty array, got size %d", arr.LenArr())
	}
	for i := 0; i < 20; i++ {
		arr.AddEnd("y")
	}
	for i := 0; i < 20; i++ {
		arr.DelHead()
	}
	if arr.LenArr() != 0 {
		t.Errorf("Expected empty after DelHead loop")
	}
	for i := 0; i < 20; i++ {
		arr.AddEnd("z")
	}
	for i := 0; i < 20; i++ {
		arr.DelAt(0)
	}
	if arr.LenArr() != 0 {
		t.Errorf("Expected empty after DelAt loop")
	}
}

func TestMyArr_Branch_EdgeCases(t *testing.T) {
	arr := NewMyArr()
	arr.ReadArray()
	arr.DelHead()
	arr.DelEnd()
	arr.DelAt(0)
	arr.RepArr(0, "val")

	arr.AddEnd("A")
	arr.AddAt(-1, "err")
	arr.AddAt(5, "err")
	arr.DelAt(-1)
	arr.DelAt(5)
	arr.RepArr(-1, "err")
	arr.RepArr(5, "err")

	if val := arr.GetAt(-1); val != "[INVALID_INDEX]" {
		t.Errorf("Expected [INVALID_INDEX], got %s", val)
	}
	if val := arr.GetAt(5); val != "[INVALID_INDEX]" {
		t.Errorf("Expected [INVALID_INDEX], got %s", val)
	}

	arr.AddHead("Head")
	arr.AddAt(1, "Mid")
	if arr.GetAt(0) != "Head" {
		t.Errorf("Expected Head at 0")
	}
	if arr.GetAt(1) != "Mid" {
		t.Errorf("Expected Mid at 1")
	}
	
	// Специфичный тест для ветки: if idx == len(a.data) { a.AddEnd(val) }
	arr.AddAt(arr.LenArr(), "TailAppend")
	if arr.GetAt(arr.LenArr()-1) != "TailAppend" {
		t.Error("AddAt at end failed")
	}
}

func TestMyArr_SaveAndLoad(t *testing.T) {
	arr := NewMyArr()
	arr.AddEnd("one")
	arr.AddEnd("two")
	filename := "arr_test.bin"
	
	if err := arr.SaveToFile(filename); err != nil {
		t.Fatalf("Save failed: %v", err)
	}
	defer os.Remove(filename)

	arr2 := NewMyArr()
	if err := arr2.LoadFromFile(filename); err != nil {
		t.Fatalf("Load failed: %v", err)
	}

	if arr2.LenArr() != 2 {
		t.Errorf("Size mismatch: expected 2, got %d", arr2.LenArr())
	}
	if arr2.GetAt(0) != "one" || arr2.GetAt(1) != "two" {
		t.Errorf("Content mismatch")
	}
}	

func TestMyArr_FullCoverage(t *testing.T) {
	arr := NewMyArr()

	arr.AddAt(0, "A")     
	arr.AddAt(5, "B")   
	arr.AddAt(-1, "C")    
	arr.AddAt(1, "Tail")   
	arr.AddAt(0, "Head")  
	
	if arr.GetAt(0) != "Head" || arr.GetAt(2) != "Tail" {
		t.Error("AddAt logic failed")
	}

	arr.DelAt(-1) 
	arr.DelAt(100) 
	arr.DelAt(1)   // Удаляем "A" (середина)
	if arr.LenArr() != 2 { t.Error("DelAt failed") }

	arr.RepArr(-1, "X")
	arr.RepArr(100, "X")
	arr.RepArr(0, "NewHead")
	if arr.GetAt(0) != "NewHead" { t.Error("RepArr failed") }

	if arr.GetAt(-5) != "[INVALID_INDEX]" { t.Error("GetAt negative failed") }
	if arr.GetAt(100) != "[INVALID_INDEX]" { t.Error("GetAt overflow failed") }

	empty := NewMyArr()
	empty.DelHead()
	empty.DelEnd()  
	empty.ReadArray() 

	arr.SaveToFile("arr_cov.txt")
	defer os.Remove("arr_cov.txt")
	arr2 := NewMyArr()
	arr2.LoadFromFile("arr_cov.txt")
	if arr2.LenArr() != arr.LenArr() { t.Error("Text Save/Load size mismatch") }

	arr.SaveToBinaryFile("arr_cov.bin")
	defer os.Remove("arr_cov.bin")
	arr3 := NewMyArr()
	arr3.LoadFromBinaryFile("arr_cov.bin")
	if arr3.GetAt(0) != "NewHead" { t.Error("Binary Save/Load val mismatch") }
}