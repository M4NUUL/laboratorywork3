
import random
import math
from collections import defaultdict

# Тип bint заменён на обычный int (в питоне он без переполнений, но для int_pow проверяем переполнение вручную)
UINT64_MAX = (1 << 64) - 1

N = 500
resheto = [True] * N
simpleNums = []

gen = random

def bit_length(x: int) -> int:
    bits = 0
    while x > 0:
        x >>= 1
        bits += 1
    return bits

def int_pow(base: int, exp: int) -> int:
    result = 1
    for _ in range(exp):
        # проверяем, не выйдет ли за UINT64_MAX
        if result > UINT64_MAX // base:
            return 0
        result *= base
    return result

def mod_pow(a: int, x: int, m: int) -> int:
    return pow(a, x, m)

def millerRabin(n: int, t: int) -> bool:
    if n < 2:
        return False
    d = n - 1
    s = 0
    while (d & 1) == 0:
        d >>= 1
        s += 1
    for _ in range(t):
        a = gen.randint(2, n - 2)
        x = mod_pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        composite = True
        for _ in range(1, s):
            x = (x * x) % n
            if x == n - 1:
                composite = False
                break
        if composite:
            return False
    return True


#РЕШЕТО ЭРАТОСФЕНА
def eratosfen():
    resheto[0] = False
    resheto[1] = False
    for i in range(2, int(math.isqrt(N)) + 1):
        if resheto[i]:
            for j in range(i * i, N, i):
                resheto[j] = False
    for i in range(2, N):
        if resheto[i]:
            simpleNums.append(i)


#МИЛЛЕР
millerOtbros = []

def millerTest(n: int, t: int, qs: list[int]) -> bool:
    randomBint = []
    for _ in range(t):
        elem = 0
        while True:
            elem = gen.randint(2, n - 1)
            if elem not in randomBint:
                break
        if mod_pow(elem, n - 1, n) != 1:
            return False
        randomBint.append(elem)
    for qi in qs:
        f = False
        for aj in randomBint:
            res = mod_pow(aj, (n - 1) // qi, n)
            if res != 1:
                f = True
                break
        if not f:
            return False
    return True

def millerGen(k: int) -> tuple[int, list[int]]:
    m = 1
    qs: list[int] = []
    while True:
        qs.clear()
        m = 1
        for _ in range(k):
            q = simpleNums[gen.randint(0, len(simpleNums) - 1)]
            qs.append(q)
            a = gen.randint(1, 5)
            elem = int_pow(q, a)
            if elem == 0 or bit_length(m) + bit_length(elem) > 63:
                m = 0
                break
            m *= elem
        if bit_length(m) == 63 and m != 0:
            break
    qs.append(2)
    qs = sorted(set(qs))
    n = 2 * m + 1
    return n, qs

def miller(k: int, t: int) -> int:
    final = 0
    while True:
        n, qs = millerGen(k)
        final = n
        if millerTest(n, t, qs):
            break
        else:
            millerOtbros.append(n)
    return final

def TestAlgMiller():
    tests: dict[int, list[int]] = {
        13: [2, 3],
        29: [2, 7],
        61: [2, 3, 5],
        97: [2, 3],
        157: [2, 13],
        173: [2, 43],
        179: [2, 89],
        353: [2, 11],
        419: [2, 11, 19],
        461: [2, 5, 23],
        617: [2, 7, 11],
        821: [2, 5, 41],
        1069: [2, 3, 89],
        5953: [2, 3, 31],
        6121: [2, 3, 5, 17],
        6197: [2, 1549],
        6373: [2, 3, 59],
        # эти всегда отвергаются
        335: [2, 167],
        437: [2, 109],
        657: [2, 41],
        779: [2, 389],
        1189: [2, 3, 11],
        1191: [2, 5, 7, 17],
        1533: [2, 383],
        1785: [2, 223],
        2071: [2, 3, 5, 23],
        2327: [2, 1163],
        2249: [2, 281],
        3057: [2, 191],
        3379: [2, 3, 563],
        4009: [2, 3, 167],
        4647: [2, 23, 101],
        5007: [2, 2503],
        5211: [2, 5, 521],
        8891: [2, 5, 7, 127],
        9451: [2, 3, 5, 7],
        9837: [2, 2459],
        9943: [2, 3, 1657],
        6141: [2, 5, 307],
        6259: [2, 3, 7, 149],
        6951: [2, 5, 139],
        7157: [2, 1789],
        7483: [2, 3, 29, 43],
    }
    for n, qs in tests.items():
        c = 0.0
        for _ in range(1000):
            if not millerTest(n, 1, qs):
                c += 1
        print(n, c / 1000)


#ПОЛИНГТОН
polingtonOtbros: list[int] = []

def polingtonTest(n: int, t: int, qs: list[int]) -> bool:
    randomBint = []
    for _ in range(t):
        elem = 0
        while True:
            elem = gen.randint(2, n - 1)
            if elem not in randomBint:
                break
        if mod_pow(elem, n - 1, n) != 1:
            return False
        randomBint.append(elem)
    for aj in randomBint:
        f = False
        for qi in qs:
            res = mod_pow(aj, (n - 1) // qi, n)
            if res == 1:
                f = True
                break
        if not f:
            return True
    return False

def polingtonGen(k: int) -> tuple[int, list[int]]:
    F = 1
    qs: list[int] = []
    while True:
        qs.clear()
        F = 1
        for _ in range(k):
            q = simpleNums[gen.randint(0, len(simpleNums) - 1)]
            qs.append(q)
            a = gen.randint(1, 5)
            elem = int_pow(q, a)
            if elem == 0 or bit_length(F) + bit_length(elem) > 31:
                F = 0
                break
            F *= elem
        if bit_length(F) == 31 and F != 0:
            break
    qs.append(2)
    qs = sorted(set(qs))

    R = 0
    while True:
        a = gen.randint(2, (1 << 31) - 1)
        if a % 2 == 0 and bit_length(F) - 1 == bit_length(a):
            R = a
            break
    n = R * F + 1
    return n, qs

def polington(k: int, t: int) -> int:
    final = 0
    while True:
        n, qs = polingtonGen(k)
        final = n
        if polingtonTest(n, t, qs):
            break
        else:
            polingtonOtbros.append(n)
    return final

def TestAlgPolington():
    tests: dict[int, list[int]] = {
        13: [2],
        29: [7],
        61: [3, 5],
        97: [3, 2],
        157: [13],
        173: [43],
        179: [89],
        353: [2, 11],
        419: [11, 19],
        461: [23],
        617: [7, 11],
        821: [41],
        1069: [89],
        5953: [3, 31],
        6121: [5, 17],
        6197: [1549],
        6373: [3, 59],
        # эти всегда отвергаются
        335: [167],
        437: [109],
        657: [41],
        779: [389],
        1189: [3, 11],
        1191: [7, 17],
        1533: [383],
        1785: [223],
        2071: [5, 23],
        2327: [1163],
        2249: [281],
        3057: [191],
        3379: [563],
        4009: [167],
        4647: [101],
        5007: [2503],
        5211: [521],
        8891: [127],
        9451: [5, 7],
        9837: [2459],
        9943: [1657],
        6141: [307],
        6259: [149],
        6951: [139],
        7157: [1789],
        7483: [29, 43],
    }
    for n, qs in tests.items():
        c = 0.0
        for _ in range(1000):
            if not polingtonTest(n, 1, qs):
                c += 1
        print(n, c / 1000)


#ГОСТ
gostOtbros: list[int] = []

def gost(q: int, t: int, c_flag: int) -> int:
    while True:
        xi = gen.random()
        if c_flag == 0:
            xi = 0.0
        A = math.ceil((2 ** (t - 1)) / q)
        B = math.ceil((2 ** (t - 1)) * xi / q)
        N = A + B
        if N % 2 == 1:
            N += 1

        u = 0
        while True:
            p = (N + u) * q + 1
            if p >= (1 << t):
                break
            if mod_pow(2, p - 1, p) == 1 and mod_pow(2, N + u, p) != 1:
                return p
            gostOtbros.append(p)
            u += 2

def TestAlgGost():
    tests: list[tuple[int, tuple[int, int]]] = [
        (13, (3, 4)),
        (41, (5, 6)),
        (29, (7, 5)),
        (31, (5, 5)),
        (67, (11, 7)),
        (199, (11, 8)),
        (79, (13, 7)),
        (131, (13, 8)),
        (307, (17, 9)),
        (613, (17, 10)),
        (419, (19, 9)),
        (277, (23, 9)),
        (349, (29, 9)),
        (311, (31, 9)),
        (2221, (37, 11)),
        (2297, (41, 11)),
        (571, (19, 10)),
        (599, (23, 10)),
    ]
    for f, (q, t) in tests:
        gostres = gost(q, t, 0)
        print(f"{q} {t} {gostres} {'=' if gostres == f else '!='} {f}")


#ВЫВОД ТАБЛИЦ
def tables():
    millerGens: list[int] = []
    millerSost: list[list[int]] = []
    for _ in range(10):
        millerOtbros.clear()
        millerGens.append(miller(5, 1))
        millerSost.append(millerOtbros.copy())

    print("Таблица для метода Миллера")
    header = "№".ljust(4)
    for i in range(1, 11):
        header += f"{i:>22}"
    print(header)
    rowP = "P".ljust(4)
    for val in millerGens:
        rowP += f"{val:>22}"
    print(rowP)
    rowRs = "Rs".ljust(4)
    for val in millerGens:
        rowRs += f"{('+ ' if millerRabin(val, 2) else '- '):>22}"
    print(rowRs)
    rowK = "K".ljust(4)
    for sost in millerSost:
        c = 0
        for j in sost:
            if millerRabin(j, 2):
                c += 1
        rowK += f"{c:>22}"
    print(rowK)

    polingtonGens: list[int] = []
    polingtonSost: list[list[int]] = []
    for _ in range(10):
        polingtonOtbros.clear()
        polingtonGens.append(polington(5, 1))
        polingtonSost.append(polingtonOtbros.copy())

    print("Таблица для метода Полингтона")
    header = "№".ljust(4)
    for i in range(1, 11):
        header += f"{i:>22}"
    print(header)

    rowP = "P".ljust(4)
    for val in polingtonGens:
        rowP += f"{val:>22}"
    print(rowP)

    rowRs = "Rs".ljust(4)
    for val in polingtonGens:
        rowRs += f"{('+ ' if millerRabin(val, 2) else '- '):>22}"
    print(rowRs)

    rowK = "K".ljust(4)
    for sost in polingtonSost:
        c = 0
        for j in sost:
            if millerRabin(j, 2):
                c += 1
        rowK += f"{c:>22}"
    print(rowK)
    print()

    gostGens: list[int] = []
    gostSost: list[list[int]] = []
    for i in range(10):
        gostOtbros.clear()
        # t = 4*(i+2) как в C++
        gostGens.append(gost(7, 4 * (i + 2), 1))
        gostSost.append(gostOtbros.copy())

    print("Таблица для метода по ГОСТ")
    header = "№".ljust(4)
    for j in range(1, 11):
        header += f"{j:>22}"
    print(header)

    rowP = "P".ljust(4)
    for val in gostGens:
        rowP += f"{val:>22}"
    print(rowP)

    rowRs = "Rs".ljust(4)
    for val in gostGens:
        rowRs += f"{('+ ' if millerRabin(val, 2) else '- '):>22}"
    print(rowRs)

    rowK = "K".ljust(4)
    for sost in gostSost:
        c = 0
        for j in sost:
            if millerRabin(j, 2):
                c += 1
        rowK += f"{c:>22}"
    print(rowK)
    print()


#ФИНАЛЬНАЯ ПРОВЕРКА
def finaltest():
    cmd = input("Желаете проверить корректность алгоритмов на данных из приложения? (1 - Да, 2 - Нет)\n")
    try:
        cmd_int = int(cmd)
    except ValueError:
        return
    if cmd_int == 1:
        print("\nМиллер:")
        TestAlgMiller()
        print("\nПолингтон:")
        TestAlgPolington()
        print("\nГОСТ:")
        TestAlgGost()

# ==================================== MAIN ====================================

if __name__ == "__main__":
    eratosfen()
    tables()
    finaltest()
