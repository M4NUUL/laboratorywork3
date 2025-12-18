package ds

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)


func hashStr(key string, mod int) int {
	h := 0
	for _, ch := range key {
		v := int(ch)
		if v < 0 {
			v = -v
		}
		h = (h*31 + v) % mod
	}
	return h
}


type ChainNode struct {
	Key  string
	Val  string
	Next *ChainNode
}

type ChainHash struct {
	Table []*ChainNode
	Cap   int
}

func NewChainHash(buckets int) *ChainHash {
	if buckets < 1 {
		buckets = 1
	}
	return &ChainHash{
		Table: make([]*ChainNode, buckets),
		Cap:   buckets,
	}
}

func (c *ChainHash) Insert(k, v string) {
	idx := hashStr(k, c.Cap)
	cur := c.Table[idx]

	for cur != nil {
		if cur.Key == k {
			cur.Val = v
			return
		}
		cur = cur.Next
	}

	c.Table[idx] = &ChainNode{
		Key:  k,
		Val:  v,
		Next: c.Table[idx],
	}
}

func (c *ChainHash) Find(key string) string {
	idx := hashStr(key, c.Cap)
	cur := c.Table[idx]
	for cur != nil {
		if cur.Key == key {
			return cur.Val
		}
		cur = cur.Next
	}
	return ""
}

func (c *ChainHash) Erase(key string) bool {
	idx := hashStr(key, c.Cap)
	cur := c.Table[idx]
	var prev *ChainNode = nil

	for cur != nil {
		if cur.Key == key {
			if prev == nil {
				// Удаление головы цепочки
				c.Table[idx] = cur.Next
			} else {
				// Удаление из середины
				prev.Next = cur.Next
			}
			return true
		}
		prev = cur
		cur = cur.Next
	}
	return false
}

func (c *ChainHash) Show() {
	fmt.Println("--- ChainHash Content ---")
	for i, node := range c.Table {
		if node != nil {
			fmt.Printf("[%d]: ", i)
			for cur := node; cur != nil; cur = cur.Next {
				fmt.Printf("(%s->%s) -> ", cur.Key, cur.Val)
			}
			fmt.Println("nil")
		}
	}
}


func (c *ChainHash) SaveToFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	fmt.Fprintln(file, c.Cap)
	cnt := 0
	for _, n := range c.Table {
		for cur := n; cur != nil; cur = cur.Next {
			cnt++
		}
	}
	fmt.Fprintln(file, cnt)

	for _, n := range c.Table {
		for cur := n; cur != nil; cur = cur.Next {
			WriteStringText(file, cur.Key)
			WriteStringText(file, cur.Val)
		}
	}
	return nil
}

func (c *ChainHash) LoadFromFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil { return err }
	defer file.Close()

	sc := bufio.NewScanner(file)
	var capVal, count int
	if sc.Scan() { fmt.Sscanf(sc.Text(), "%d", &capVal) }

	c.Cap = capVal
	c.Table = make([]*ChainNode, c.Cap)

	if sc.Scan() { fmt.Sscanf(sc.Text(), "%d", &count) }

	for i := 0; i < count; i++ {
		k := ReadStringText(sc)
		v := ReadStringText(sc)
		c.Insert(k, v)
	}
	return nil
}


func (c *ChainHash) SaveToBinaryFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	WriteInt32(file, int32(c.Cap))
	count := 0
	for _, n := range c.Table {
		for cur := n; cur != nil; cur = cur.Next {
			count++
		}
	}
	WriteInt32(file, int32(count))

	for _, n := range c.Table {
		for cur := n; cur != nil; cur = cur.Next {
			WriteString(file, cur.Key)
			WriteString(file, cur.Val)
		}
	}
	return nil
}

func (c *ChainHash) LoadFromBinaryFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil { return err }
	defer file.Close()

	capVal, _ := ReadInt32(file)
	c.Cap = int(capVal)
	c.Table = make([]*ChainNode, c.Cap)

	count, _ := ReadInt32(file)
	for i := 0; i < int(count); i++ {
		k, _ := ReadString(file)
		v, _ := ReadString(file)
		c.Insert(k, v)
	}
	return nil
}


type OpenEntry struct {
	Key     string
	Val     string
	Used    bool
	Deleted bool
}

type OpenHash struct {
	Table []OpenEntry
	Cap   int
}

func NewOpenHash(size int) *OpenHash {
	if size < 1 {
		size = 1
	}
	return &OpenHash{
		Table: make([]OpenEntry, size),
		Cap:   size,
    }
}

func (o *OpenHash) Insert(k, v string) {
	idx := hashStr(k, o.Cap)
	start := idx

	for {
		e := &o.Table[idx]

		if !e.Used && !e.Deleted {
			e.Key = k
			e.Val = v
			e.Used = true
			return
		}
		if e.Used && e.Key == k {
			e.Val = v
			return
		}
		if e.Deleted {
			e.Key = k
			e.Val = v
			e.Used = true
			e.Deleted = false
			return
		}

		idx = (idx + 1) % o.Cap
		if idx == start {
			fmt.Println("OpenHash full!")
			return
		}
	}
}

func (o *OpenHash) Find(k string) string {
	idx := hashStr(k, o.Cap)
	start := idx

	for {
		e := &o.Table[idx]

		if e.Used && e.Key == k {
			return e.Val
		}
		// Если слот пуст и не удален, значит элемента точно нет
		if !e.Used && !e.Deleted {
			return ""
		}

		idx = (idx + 1) % o.Cap
		if idx == start {
			return ""
		}
	}
}

func (o *OpenHash) Erase(k string) bool {
	idx := hashStr(k, o.Cap)
	start := idx

	for {
		e := &o.Table[idx]

		if e.Used && e.Key == k {
			e.Used = false
			e.Deleted = true // Важно для линейного пробирования
			return true
		}
		
		if !e.Used && !e.Deleted {
			return false
		}

		idx = (idx + 1) % o.Cap
		if idx == start {
			return false
		}
	}
}

func (o *OpenHash) Show() {
	fmt.Println("--- OpenHash Content ---")
	for i, e := range o.Table {
		status := "EMPTY"
		if e.Used {
			status = fmt.Sprintf("%s->%s", e.Key, e.Val)
		} else if e.Deleted {
			status = "DELETED"
		}
		fmt.Printf("[%d]: %s\n", i, status)
	}
}


func (o *OpenHash) SaveToFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	fmt.Fprintln(file, o.Cap)
	count := 0
	for _, e := range o.Table {
		if e.Used { count++ }
	}
	fmt.Fprintln(file, count)

	for _, e := range o.Table {
		if e.Used {
			WriteStringText(file, e.Key)
			WriteStringText(file, e.Val)
		}
	}
	return nil
}

func (o *OpenHash) LoadFromFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil { return err }
	defer file.Close()

	sc := bufio.NewScanner(file)
	var capVal, count int
	if sc.Scan() { fmt.Sscanf(sc.Text(), "%d", &capVal) }
	o.Cap = capVal
	o.Table = make([]OpenEntry, capVal)

	if sc.Scan() { fmt.Sscanf(sc.Text(), "%d", &count) }

	for i := 0; i < count; i++ {
		k := ReadStringText(sc)
		v := ReadStringText(sc)
		o.Insert(k, v)
	}
	return nil
}

func (o *OpenHash) SaveToBinaryFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil { return err }
	defer file.Close()

	WriteInt32(file, int32(o.Cap))
	count := 0
	for _, e := range o.Table {
		if e.Used { count++ }
	}
	WriteInt32(file, int32(count))

	for _, e := range o.Table {
		if e.Used {
			WriteString(file, e.Key)
			WriteString(file, e.Val)
		}
	}
	return nil
}

func (o *OpenHash) LoadFromBinaryFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil { return err }
	defer file.Close()

	capVal, _ := ReadInt32(file)
	o.Cap = int(capVal)
	o.Table = make([]OpenEntry, o.Cap)

	count, _ := ReadInt32(file)
	for i := 0; i < int(count); i++ {
		k, _ := ReadString(file)
		v, _ := ReadString(file)
		o.Insert(k, v)
	}
	return nil
}

func HashMan() {
	scanner := bufio.NewScanner(os.Stdin)
	ch := NewChainHash(10)
	oh := NewOpenHash(10)
	
	currentMode := "chain" 

	fmt.Println("Хеш-менеджер. Команды: CHAIN, OPEN, INSERT k v, SEARCH k, DELETE k, SHOW, BACK")
	
	for {
		fmt.Printf("[%s] >> ", currentMode)
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		parts := strings.Fields(line)
		if len(parts) == 0 { continue }

		cmd := parts[0]
		
		switch cmd {
		case "BACK":
			return
		case "CHAIN":
			currentMode = "chain"
			fmt.Println("Переключено на ChainHash")
		case "OPEN":
			currentMode = "open"
			fmt.Println("Переключено на OpenHash")
		case "SHOW":
			if currentMode == "chain" { ch.Show() } else { oh.Show() }
		case "INSERT":
			if len(parts) < 3 { fmt.Println("Нужен ключ и значение"); continue }
			if currentMode == "chain" { ch.Insert(parts[1], parts[2]) } else { oh.Insert(parts[1], parts[2]) }
		case "SEARCH":
			if len(parts) < 2 { fmt.Println("Нужен ключ"); continue }
			res := ""
			if currentMode == "chain" { res = ch.Find(parts[1]) } else { res = oh.Find(parts[1]) }
			if res == "" { fmt.Println("Не найдено") } else { fmt.Println("Найдено:", res) }
		case "DELETE":
			if len(parts) < 2 { fmt.Println("Нужен ключ"); continue }
			ok := false
			if currentMode == "chain" { ok = ch.Erase(parts[1]) } else { ok = oh.Erase(parts[1]) }
			if ok { fmt.Println("Удалено") } else { fmt.Println("Не найдено для удаления") }
		default:
			fmt.Println("Неизвестная команда")
		}
	}
}