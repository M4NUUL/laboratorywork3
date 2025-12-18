package ds

import (
	"encoding/binary"
	"os"
	"testing"
)

func TestIO_CommonErrors(t *testing.T) {
	arr := NewMyArr()


	if err := arr.SaveToFile("."); err == nil {
		t.Error("SaveToFile should fail when writing to a directory")
	}

	// Загрузка несуществующего файла
	if err := arr.LoadFromFile("non_existent_file_999.txt"); err == nil {
		t.Error("LoadFromFile should fail on missing file")
	}
}

//проверяет устойчивость к битым текст файлам
func Test_TextDeserialization_Corrupt(t *testing.T) {
	filename := "corrupt_text.txt"
	defer os.Remove(filename)
	
	arr := NewMyArr()


	f, _ := os.Create(filename)
	f.Close()
	
	if err := arr.LoadFromFile(filename); err == nil {
		t.Error("LoadFromFile (Text) should fail on empty file")
	}


	os.WriteFile(filename, []byte("NOT_A_NUMBER\nData"), 0644)
	
	if err := arr.LoadFromFile(filename); err == nil {
		t.Error("LoadFromFile (Text) should fail on invalid header")
	}
}

//проверяет устойчивость к битым бин файлам
func Test_BinaryDeserialization_Corrupt(t *testing.T) {
	filename := "corrupt_bin.bin"
	defer os.Remove(filename)

	arr := NewMyArr()


	os.WriteFile(filename, []byte{0xFF}, 0644)
	
	if err := arr.LoadFromBinaryFile(filename); err == nil {
		t.Error("LoadFromBinaryFile should fail on truncated header (filesize < 4 bytes)")
	}

	f, _ := os.Create(filename)
	binary.Write(f, binary.LittleEndian, int32(1)) 
	f.Close()

	if err := arr.LoadFromBinaryFile(filename); err == nil {
		t.Error("LoadFromBinaryFile should fail on missing body data")
	}
}