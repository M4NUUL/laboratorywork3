#include <benchmark/benchmark.h>
#include "arr.h"
#include "list.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hash.h"
#include "compl.h"


static void BM_DynArr_PushEnd(benchmark::State& state) {
    for (auto _ : state) {
        MyArr arr;
        for (int i = 0; i < state.range(0); i++)
            arr.addEnd("X");
    }
}
BENCHMARK(BM_DynArr_PushEnd)->Range(1000, 100000);

static void BM_List_AddTail(benchmark::State& state) {
    for (auto _ : state) {
        MyList l;
        for (int i = 0; i < state.range(0); i++)
            l.addTail("X");
    }
}
BENCHMARK(BM_List_AddTail)->Range(1000, 100000);

static void BM_DList_AddTail(benchmark::State& state) {
    for (auto _ : state) {
        DList l;
        for (int i = 0; i < state.range(0); i++)
            l.addTail("Y");
    }
}
BENCHMARK(BM_DList_AddTail)->Range(1000, 100000);


static void BM_Stack_PushPop(benchmark::State& state) {
    for (auto _ : state) {
        Stack s;
        for (int i = 0; i < state.range(0); i++)
            s.push("A");
        for (int i = 0; i < state.range(0); i++)
            s.pop();
    }
}
BENCHMARK(BM_Stack_PushPop)->Range(1000, 100000);


static void BM_Queue_PushPop(benchmark::State& state) {
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < state.range(0); i++)
            q.push("A");
        for (int i = 0; i < state.range(0); i++)
            q.pop();
    }
}
BENCHMARK(BM_Queue_PushPop)->Range(1000, 100000);


static void BM_CBT_Insert(benchmark::State& state) {
    for (auto _ : state) {
        CompleteBinaryTree t;
        for (int i = 0; i < state.range(0); i++)
            t.insert(i);
    }
}
BENCHMARK(BM_CBT_Insert)->Range(1000, 50000);

static void BM_CBT_Search(benchmark::State& state) {
    CompleteBinaryTree t;
    for (int i = 0; i < state.range(0); i++)
        t.insert(i);

    for (auto _ : state)
        t.search(state.range(0) / 2);
}
BENCHMARK(BM_CBT_Search)->Range(1000, 50000);





static void BM_ChainHash_Insert(benchmark::State& state) {
    for (auto _ : state) {
        ChainHash h(1000);
        for (int i = 0; i < state.range(0); i++)
            h.insert(std::to_string(i), "X");
    }
}
BENCHMARK(BM_ChainHash_Insert)->Range(1000, 50000);


static void BM_OpenHash_Insert(benchmark::State& state) {
    for (auto _ : state) {
        OpenHash h(state.range(0) * 2);
        for (int i = 0; i < state.range(0); i++)
            h.insert(std::to_string(i), "X");
    }
}
BENCHMARK(BM_OpenHash_Insert)->Range(1000, 50000);


BENCHMARK_MAIN();
