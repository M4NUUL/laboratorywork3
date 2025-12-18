package ds

import (
	"fmt"
	"testing"
)

// Наборы диапазонов, совпадающие с примером C++
var rangesStandard = []int{1000, 4096, 32768, 100000}
var rangesTreeHash = []int{1000, 4096, 32768, 50000}

// --- MyArr (Динамический массив) ---
func BenchmarkDynArr_PushEnd(b *testing.B) {
	for _, n := range rangesStandard {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				arr := NewMyArr()
				for j := 0; j < n; j++ {
					arr.AddEnd("X")
				}
			}
		})
	}
}

// --- MyList (Односвязный список) ---
func BenchmarkList_AddTail(b *testing.B) {
	for _, n := range rangesStandard {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				l := NewMyList()
				for j := 0; j < n; j++ {
					l.AddTail("X")
				}
			}
		})
	}
}

// --- DList (Двусвязный список) ---
func BenchmarkDList_AddTail(b *testing.B) {
	for _, n := range rangesStandard {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				dl := NewDList()
				for j := 0; j < n; j++ {
					dl.AddTail("Y")
				}
			}
		})
	}
}

// --- Stack (Стек) ---
func BenchmarkStack_PushPop(b *testing.B) {
	for _, n := range rangesStandard {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				s := NewStack()
				// Сначала N Push
				for j := 0; j < n; j++ {
					s.Push("A")
				}
				// Затем N Pop
				for j := 0; j < n; j++ {
					s.Pop()
				}
			}
		})
	}
}

// --- Queue (Очередь) ---
func BenchmarkQueue_PushPop(b *testing.B) {
	for _, n := range rangesStandard {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				q := NewQueue()
				for j := 0; j < n; j++ {
					q.Push("A")
				}
				for j := 0; j < n; j++ {
					q.Pop()
				}
			}
		})
	}
}

// --- CBT (Complete Binary Tree) ---

func BenchmarkCBT_Insert(b *testing.B) {
	for _, n := range rangesTreeHash {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				t := NewCBT()
				for j := 0; j < n; j++ {
					t.Insert(j)
				}
			}
		})
	}
}

func BenchmarkCBT_Search(b *testing.B) {
	for _, n := range rangesTreeHash {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			// Подготовка: создаем дерево один раз перед замером
			b.StopTimer()
			t := NewCBT()
			for j := 0; j < n; j++ {
				t.Insert(j)
			}
			target := n / 2
			b.StartTimer()

			// Замеряем только поиск
			for i := 0; i < b.N; i++ {
				t.Search(target)
			}
		})
	}
}

// --- Хеш-таблицы ---

func BenchmarkChainHash_Insert(b *testing.B) {
	for _, n := range rangesTreeHash {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				h := NewChainHash(1000) // Размер бакетов как в C++ (1000)
				for j := 0; j < n; j++ {
					key := fmt.Sprintf("%d", j)
					h.Insert(key, "X")
				}
			}
		})
	}
}

func BenchmarkOpenHash_Insert(b *testing.B) {
	for _, n := range rangesTreeHash {
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				h := NewOpenHash(n * 2) // Размер x2 от кол-ва элементов
				for j := 0; j < n; j++ {
					key := fmt.Sprintf("%d", j)
					h.Insert(key, "X")
				}
			}
		})
	}
}