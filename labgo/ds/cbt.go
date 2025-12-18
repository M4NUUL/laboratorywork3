package ds

import (
    "fmt"
    "os"
)

type CBTNode struct {
    Data  int32
    Left  *CBTNode
    Right *CBTNode
}

type CompleteBinaryTree struct {
    Root *CBTNode
    Size int
}


func NewCBT() *CompleteBinaryTree {
    return &CompleteBinaryTree{Root: nil, Size: 0}
}

func (t *CompleteBinaryTree) insertRec(node *CBTNode, value int32) *CBTNode {
    if node == nil {
        t.Size++
        return &CBTNode{Data: value}
    }
    if value < node.Data {
        node.Left = t.insertRec(node.Left, value)
    } else if value > node.Data {
        node.Right = t.insertRec(node.Right, value)
    }
    return node
}

func (t *CompleteBinaryTree) Insert(value int) {
    t.Root = t.insertRec(t.Root, int32(value))
}

func (t *CompleteBinaryTree) findMin(node *CBTNode) *CBTNode {
    for node != nil && node.Left != nil {
        node = node.Left
    }
    return node
}

func (t *CompleteBinaryTree) deleteNodeRec(node *CBTNode, value int32) *CBTNode {
    if node == nil {
        return nil
    }

    if value < node.Data {
        node.Left = t.deleteNodeRec(node.Left, value)
    } else if value > node.Data {
        node.Right = t.deleteNodeRec(node.Right, value)
    } else {
        if node.Left == nil {
            t.Size--
            return node.Right
        }
        if node.Right == nil {
            t.Size--
            return node.Left
        }
        successor := t.findMin(node.Right)
        node.Data = successor.Data
        node.Right = t.deleteNodeRec(node.Right, successor.Data)
    }
    return node
}

func (t *CompleteBinaryTree) Remove(value int) {
    if t.Root == nil {
        return
    }
    t.Root = t.deleteNodeRec(t.Root, int32(value))
}

func (t *CompleteBinaryTree) Search(value int) bool {
    val := int32(value)
    cur := t.Root
    for cur != nil {
        if cur.Data == val {
            return true
        }
        if val < cur.Data {
            cur = cur.Left
        } else {
            cur = cur.Right
        }
    }
    return false
}

func (t *CompleteBinaryTree) Contains(value int) bool {
    return t.Search(value)
}

func (t *CompleteBinaryTree) Print() {
    if t.Root == nil {
        fmt.Println("Дерево пусто")
        return
    }
    t.inOrderRec(t.Root)
    fmt.Println()
}

func (t *CompleteBinaryTree) InorderPrint() {
    t.Print()
}

func (t *CompleteBinaryTree) inOrderRec(n *CBTNode) {
    if n == nil {
        return
    }
    t.inOrderRec(n.Left)
    fmt.Printf("%d ", n.Data)
    t.inOrderRec(n.Right)
}

func (t *CompleteBinaryTree) Clear() {
    t.Root = nil
    t.Size = 0
}

// Добавлено: метод для пересчета размера
func (t *CompleteBinaryTree) countNodes(n *CBTNode) int {
    if n == nil { return 0 }
    return 1 + t.countNodes(n.Left) + t.countNodes(n.Right)
}


func (t *CompleteBinaryTree) SaveToFile(filename string) error {
    return SaveCBTText(filename, t.Root)
}

func (t *CompleteBinaryTree) LoadFromFile(filename string) error {
    root, err := LoadCBTText(filename)
    if err != nil {
        return err
    }
    t.Root = root
    t.Size = t.countNodes(t.Root) // Исправлено: обновляем Size
    return nil
}


func writeBinaryRec(n *CBTNode, f *os.File) error {
    if n == nil {
        return WriteInt32(f, -1)
    }
    if err := WriteInt32(f, n.Data); err != nil {
        return err
    }
    if err := writeBinaryRec(n.Left, f); err != nil {
        return err
    }
    return writeBinaryRec(n.Right, f)
}

func (t *CompleteBinaryTree) SaveToBinaryFile(filename string) error {
    file, err := os.Create(filename)
    if err != nil {
        return err
    }
    defer file.Close()
    return writeBinaryRec(t.Root, file)
}

func readBinaryRec(f *os.File) (*CBTNode, error) {
    val, err := ReadInt32(f)
    if err != nil {
        return nil, err
    }
    if val == -1 {
        return nil, nil
    }
    node := &CBTNode{Data: val}
    node.Left, err = readBinaryRec(f)
    if err != nil {
        return nil, err
    }
    node.Right, err = readBinaryRec(f)
    if err != nil {
        return nil, err
    }
    return node, nil
}

func (t *CompleteBinaryTree) LoadFromBinaryFile(filename string) error {
    file, err := os.Open(filename)
    if err != nil {
        return err
    }
    defer file.Close()

    t.Clear()
    root, err := readBinaryRec(file)
    if err != nil {
        return err
    }
    t.Root = root
    t.Size = t.countNodes(t.Root) // Исправлено: обновляем Size
    return nil
}