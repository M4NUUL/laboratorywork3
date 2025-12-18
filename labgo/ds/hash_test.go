package ds

import (
	"os"
	"testing"
)

func TestHash_ChainHash_Coverage(t *testing.T) {
	ch := NewChainHash(1)
	ch.Show() 

	ch.Insert("A", "1")
	ch.Insert("B", "2")
	ch.Insert("C", "3")

	if val := ch.Find("B"); val != "2" {
		t.Errorf("Find failed deep in chain. Expected 2, got %s", val)
	}
	if val := ch.Find("C"); val != "3" {
		t.Errorf("Find failed at end of chain. Expected 3, got %s", val)
	}

	// Обновление значения
	ch.Insert("B", "222")
	if val := ch.Find("B"); val != "222" {
		t.Errorf("Update failed. Expected 222, got %s", val)
	}

	
	ch.Erase("B")
	if ch.Find("B") != "" {
		t.Error("B should be erased")
	}
	// Проверяем, что цепочка не порвалась
	if ch.Find("A") != "1" || ch.Find("C") != "3" {
		t.Error("Chain broken after erase")
	}

	// Удаление головы
	ch.Erase("C")
	if ch.Find("C") != "" {
		t.Error("C (head) should be erased")
	}
	
	// Удаление последнего
	ch.Erase("A")
	if ch.Find("A") != "" {
		t.Error("A should be erased")
	}

	// Удаление несуществующего
	if ch.Erase("Z") {
		t.Error("Erase Z should return false")
	}
}

func TestHash_OpenHash_Coverage(t *testing.T) {
	// Маленький размер для коллизий
	oh := NewOpenHash(2)
	oh.Show()

	// Заполняем полностью
	oh.Insert("A", "1")
	oh.Insert("B", "2")
	
	// Попытка вставить в переполненную таблицу
	oh.Insert("C", "3") 

	// Проверка поиска
	if oh.Find("A") != "1" || oh.Find("B") != "2" {
		t.Error("Find basic failed")
	}
	if oh.Find("Z") != "" {
		t.Error("Found non-existent Z")
	}

	// Проверка обновления
	oh.Insert("A", "111")
	if oh.Find("A") != "111" {
		t.Error("Update failed")
	}

	oh.Erase("A")
	if oh.Find("A") != "" {
		t.Error("A should be deleted")
	}
	oh.Insert("A", "NewA")
	if oh.Find("A") != "NewA" {
		t.Error("Insert into deleted slot failed")
	}
	
	if oh.Erase("Z") {
		t.Error("Erase non-existent should return false")
	}
}

func TestHash_SaveLoad(t *testing.T) {
	filename := "hash_test.bin"
	defer os.Remove(filename)

	ch := NewChainHash(5)
	ch.Insert("key1", "val1")
	ch.SaveToFile(filename)
	
	ch2 := NewChainHash(1)
	ch2.LoadFromFile(filename)
	if ch2.Find("key1") != "val1" {
		t.Error("ChainHash Save/Load failed")
	}

	oh := NewOpenHash(5)
	oh.Insert("k1", "v1")
	oh.SaveToFile(filename)

	oh2 := NewOpenHash(1)
	oh2.LoadFromFile(filename)
	if oh2.Find("k1") != "v1" {
		t.Error("OpenHash Save/Load failed")
	}
}

func TestHashMan_Simulation(t *testing.T) {

	r, w, _ := os.Pipe()
	origStdin := os.Stdin
	os.Stdin = r
	defer func() { os.Stdin = origStdin }()

	go func() {
		w.Write([]byte("INSERT k1 v1\nSHOW\nSEARCH k1\nDELETE k1\nSEARCH k1\nBAD_CMD\nBACK\n"))
		w.Close()
	}()

	HashMan()
}

func TestHash_Chain_Coverage(t *testing.T) {
	ch := NewChainHash(1)
	
	ch.Insert("A", "1")
	ch.Insert("B", "2") 
	
	ch.Insert("A", "11")
	if ch.Find("A") != "11" { t.Error("Update A failed") }
	
	ch.Insert("C", "3") 
	ch.Erase("B")
	if ch.Find("B") != "" { t.Error("Erase B failed") }
	if ch.Find("C") != "3" || ch.Find("A") != "11" { t.Error("Chain broken") }

	ch.Erase("C")
	if ch.Find("C") != "" { t.Error("Erase C failed") }

	if ch.Erase("Z") { t.Error("Erase Z should be false") }

	ch.SaveToFile("ch.txt")
	defer os.Remove("ch.txt")
	ch2 := NewChainHash(1)
	ch2.LoadFromFile("ch.txt")
	if ch2.Find("A") != "11" { t.Error("Load txt failed") }

	ch.SaveToBinaryFile("ch.bin")
	defer os.Remove("ch.bin")
	ch3 := NewChainHash(1)
	ch3.LoadFromBinaryFile("ch.bin")
	if ch3.Find("A") != "11" { t.Error("Load bin failed") }
}

func TestHash_Open_Coverage(t *testing.T) {
	oh := NewOpenHash(2)
	oh.Show() 
	
	oh.Insert("A", "1")
	oh.Insert("B", "2")
	
	oh.Insert("C", "3") 
	
	if oh.Find("A") != "1" { t.Error("Find A fail") }
	if oh.Find("Z") != "" { t.Error("Find Z fail") }
	
	oh.Insert("A", "11")
	if oh.Find("A") != "11" { t.Error("Update A fail") }

	oh.Erase("A")
	if oh.Find("A") != "" { t.Error("Should be deleted") }
	
	oh.Insert("A", "22") 
	if oh.Find("A") != "22" { t.Error("Reuse slot fail") }

	if oh.Erase("ZZ") { t.Error("Erase missing fail") }

	oh.SaveToFile("oh.txt")
	defer os.Remove("oh.txt")
	oh2 := NewOpenHash(2)
	oh2.LoadFromFile("oh.txt")
	if oh2.Find("B") != "2" { t.Error("Load txt fail") }

	oh.SaveToBinaryFile("oh.bin")
	defer os.Remove("oh.bin")
	oh3 := NewOpenHash(2)
	oh3.LoadFromBinaryFile("oh.bin")
	if oh3.Find("B") != "2" { t.Error("Load bin fail") }
	
	bad := NewOpenHash(0)
	if bad.Cap != 1 { t.Error("Min cap fail") }
}

func TestHashMan_Run(t *testing.T) {
	r, w, _ := os.Pipe()
	origStdin := os.Stdin
	os.Stdin = r
	defer func() { os.Stdin = origStdin }()

	go func() {
		w.Write([]byte("CHAIN\nINSERT k1 v1\nSHOW\nOPEN\nINSERT k2 v2\nSEARCH k2\nDELETE k2\nBAD\nBACK\n"))
		w.Close()
	}()
	
	HashMan()
}