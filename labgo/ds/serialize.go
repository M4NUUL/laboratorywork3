package ds

import (
	"bufio"
	"encoding/binary"
	"fmt"
	"io"
	"os"
	"strings"
)


func SaveStringsText(filename string, data []string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	fmt.Fprintln(file, len(data))
	for _, v := range data {
		fmt.Fprintln(file, v)
	}
	return nil
}

func LoadStringsText(filename string) ([]string, error) {
	file, err := os.Open(filename)
	if err != nil { return nil, err }
	defer file.Close()

	sc := bufio.NewScanner(file)
	if !sc.Scan() {
		return nil, fmt.Errorf("empty file")
	}

	var count int
	if _, err := fmt.Sscanf(sc.Text(), "%d", &count); err != nil {
        return nil, err
    }

	result := make([]string, 0, count)
	for i := 0; i < count; i++ {
		if !sc.Scan() {
			return nil, fmt.Errorf("unexpected EOF")
		}
		result = append(result, strings.TrimSpace(sc.Text()))
	}
	return result, nil
}

func WriteStringText(f io.Writer, s string) {
	fmt.Fprintln(f, s)
}

func ReadStringText(scanner *bufio.Scanner) string {
	if scanner.Scan() {
		return scanner.Text()
	}
	return ""
}


func SaveStringsBinary(filename string, data []string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	if err := binary.Write(file, binary.LittleEndian, int32(len(data))); err != nil {
		return err
	}

	for _, v := range data {
		if err := WriteString(file, v); err != nil {
			return err
		}
	}
	return nil
}

func LoadStringsBinary(filename string) ([]string, error) {
	file, err := os.Open(filename)
	if err != nil { return nil, err }
	defer file.Close()

	var count int32
	if err := binary.Read(file, binary.LittleEndian, &count); err != nil {
		return nil, err
	}

	result := make([]string, 0, count)
	for i := int32(0); i < count; i++ {
		v, err := ReadString(file)
		if err != nil {
			return nil, err
		}
		result = append(result, v)
	}
	return result, nil
}


func WriteInt32(w io.Writer, v int32) error {
	return binary.Write(w, binary.LittleEndian, v)
}

func ReadInt32(r io.Reader) (int32, error) {
	var v int32
	err := binary.Read(r, binary.LittleEndian, &v)
	return v, err
}

func WriteString(w io.Writer, s string) error {
	//Пишем длину
	if err := WriteInt32(w, int32(len(s))); err != nil {
		return err
	}
	//Пишем байты
	_, err := w.Write([]byte(s))
	return err
}

func ReadString(r io.Reader) (string, error) {
	ln, err := ReadInt32(r)
	if err != nil {
		return "", err
	}
	buf := make([]byte, ln)
	n, err := io.ReadFull(r, buf)
	if err != nil {
		return "", err
	}
	if int32(n) != ln {
		return "", fmt.Errorf("unexpected EOF")
	}
	return string(buf), nil
}


func SaveCBTText(filename string, root *CBTNode) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	var dfs func(n *CBTNode)
	dfs = func(n *CBTNode) {
		if n == nil {
			fmt.Fprintln(file, "#")
			return
		}
		fmt.Fprintln(file, n.Data)
		dfs(n.Left)
		dfs(n.Right)
	}
	dfs(root)
	return nil
}

func LoadCBTText(filename string) (*CBTNode, error) {
	file, err := os.Open(filename)
	if err != nil { return nil, err }
	defer file.Close()

	sc := bufio.NewScanner(file)
	tokens := []string{}
	for sc.Scan() {
		tokens = append(tokens, strings.TrimSpace(sc.Text()))
	}

	pos := 0
	var dfs func() *CBTNode
	dfs = func() *CBTNode {
		if pos >= len(tokens) { return nil }
		t := tokens[pos]
		pos++
		if t == "#" { return nil }
		var val int32
		fmt.Sscanf(t, "%d", &val)
		n := &CBTNode{Data: val}
		n.Left = dfs()
		n.Right = dfs()
		return n
	}
	return dfs(), nil
}