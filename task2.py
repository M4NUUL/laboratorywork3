import math
import random

# Возведение a в степень b по модулю m
def pow_mod(a, b, m):
    result = 1
    a = a % m
    while b > 0:
        if b % 2 == 1:
            result = (result * a) % m
        a = (a * a) % m
        b //= 2
    return result

# Сито Эратосфена для поиска простых чисел
def sieve(limit):
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False
    primes = []
    for i in range(2, limit + 1):
        if is_prime[i]:
            primes.append(i)
            for j in range(i * i, limit + 1, i):
                is_prime[j] = False
    return primes

# Тест Миллера
def miller_test(n, t):
    if n < 2:
        return False
    s = 0
    d = n - 1
    while d % 2 == 0:
        d //= 2
        s += 1
    for _ in range(t):
        a = random.randint(2, n - 2)
        x = pow_mod(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(1, s):
            x = pow_mod(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

# Тест Поклингтона
def poklington_test(n, F, F_factors, t):
    R = (n - 1) // F
    for _ in range(t):
        a = random.randint(2, n - 2)
        if pow_mod(a, n - 1, n) != 1:
            return False
        for q in F_factors:
            if pow_mod(a, (n - 1) // q, n) == 1:
                break
        else:
            return True
    return False

# Тест ГОСТ
def gost_test(q, t):
    R = 2
    while True:
        n = q * R + 1
        if n >= (1 << t):
            break
        a = 2
        if pow_mod(a, n - 1, n) == 1 and pow_mod(a, (n - 1) // q, n) != 1:
            return True
        R += 2
    return False

# Генератор кандидата на простое число с помощью теста Миллера
def generate_candidate_miller(primes, min_bits):
    while True:
        m = 1
        for _ in range(3):
            q = random.choice(primes)
            alpha = random.randint(1, 3)
            for _ in range(alpha):
                m *= q
        n = 2 * m + 1
        if (1 << (min_bits - 1)) <= n < (1 << min_bits):
            if miller_test(n, 5):
                return n

# Генератор кандидата на простое число с помощью теста Поклингтона
def generate_candidate_pocklington(primes, bit_size=10):
    while True:
        F = 1
        used = set()
        F_factors = []
        while len(F_factors) < 3:
            q = random.choice(primes)
            if q in used:
                continue
            used.add(q)
            F_factors.append(q)
            F *= q
        R = 2 * (1 + random.randint(0, F // 4))
        n = R * F + 1
        if (1 << (bit_size - 1)) <= n < (1 << bit_size):
            if poklington_test(n, F, F_factors, 5):
                return n

# Генерация кандидатов на простые числа с помощью теста ГОСТ
def generate_candidate_gost(primes, t_bits=10):
    q_size = t_bits // 2
    q_candidates = [p for p in primes if (1 << (q_size - 1)) <= p < (1 << q_size)]
    while True:
        q = random.choice(q_candidates)
        maxR = 4 * (q + 1)
        for R in range(2, maxR, 2):
            n = q * R + 1
            if (1 << (t_bits - 1)) <= n < (1 << t_bits):
                if gost_test(q, t_bits):
                    return n

# Универсальная функция для проверки кандидатов разными тестами
def run_test_and_print_table(method_name, candidates, test_func, t_initial=5, t_retry=10):
    results = []
    k = 0
    for num in candidates:
        passed = test_func(num, t_initial)
        false_reject = False
        if not passed and test_func(num, t_retry):
            false_reject = True
            k += 1
        results.append((num, passed, false_reject))
    print(f"\nРезультаты для метода: {method_name}")
    print("№\tP\t\tРезультат\tK")
    for i, (number, passed, false_reject) in enumerate(results, 1):
        print(f"{i}\t{number}\t\t{'+' if passed else '-'}\t\t{1 if false_reject else 0}")
    print(f"Общее количество ложных отказов (k): {k}")

# Функция для генерации фиксированного кандидата на простое число по ГОСТ
def generate_gost_fixed(q, t):
    N = (1 << (t - 1)) // q
    if N % 2 != 0:
        N += 1
    u = 0
    while True:
        p = (N + u) * q + 1
        if p >= (1 << t):
            break
        if pow_mod(2, p - 1, p) == 1 and pow_mod(2, (p - 1) // q, p) != 1:
            return p
        u += 2
    return -1

if __name__ == "__main__":
    random.seed()
    primes = sieve(500)

    # Миллер
    miller_primes = [generate_candidate_miller(primes, 10) for _ in range(10)]
    run_test_and_print_table("Miller", miller_primes, miller_test)

    # Поклингтон
    pocklington_primes = [generate_candidate_pocklington(primes, 10) for _ in range(10)]
    run_test_and_print_table("Pocklington", pocklington_primes, miller_test)  # Можно заменить на свой тест

    # ГОСТ
    gost_primes = [generate_candidate_gost(primes, 10) for _ in range(10)]
    run_test_and_print_table("GOST", gost_primes, miller_test)  # Можно заменить на свой тест

    # Проверка составных чисел тестом Миллера
    composite_miller = [335, 437, 657, 779, 1189, 1191, 1533, 1785, 2071]
    print("Проверка составных чисел тестом Миллера:")
    for n in composite_miller:
        result = miller_test(n, 5)
        print(f"{n}\t→ {'[ОШИБКА: определено как простое]' if result else 'составное'}")

    # Проверка генерации по ГОСТ (ξ=0)
    gost_cases = [
        (3, 4, 13),
        (5, 6, 41),
        (11, 8, 199),
        (17, 10, 613)
    ]
    print("Проверка генерации по ГОСТ (ξ=0):")
    for q, t, expected in gost_cases:
        p = generate_gost_fixed(q, t)
        print(f"Ожидалось: {expected}, Получено: {p}{' [ОК]' if p == expected else ' [ОШИБКА]'}")