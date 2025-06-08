import random
import math
from collections import Counter

def pow_mod(base, exp, mod):
    res = 1
    base %= mod
    while exp > 0:
        if exp % 2 == 1:
            res = (res * base) % mod
        base = (base * base) % mod
        exp //= 2
    return res

def prime_factors(num):
    factors = set()
    while num % 2 == 0:
        factors.add(2)
        num //= 2
    limit = int(math.sqrt(num)) + 1
    for i in range(3, limit, 2):
        while num % i == 0:
            factors.add(i)
            num //= i
    if num > 1:
        factors.add(num)
    return list(factors)

def filter_miller_rabin(n, k):
    if n < 2:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0:
        return False
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow_mod(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(s - 1):
            x = pow_mod(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

def proverka_osnovnaya_s_faktorami(n, k_bases, factors):
    if not factors:
        return False
    for _ in range(k_bases):
        a = random.randint(2, n - 1)
        if pow_mod(a, n - 1, n) != 1:
            continue
        for q in factors:
            if pow_mod(a, (n - 1) // q, n) == 1:
                break
        else:
            return True
    return False

def main():
    NUM_EXPERIMENTS_TARGET = 10
    OSNOVNOY_TEST_BASES = 5
    FILTER_ITERATIONS = 5
    USE_FILTER = True
    min_p = 2
    max_p = 500
    experiment_numbers = []
    numbers_tested = []
    results = []
    iterations_used = []
    all_used_bases = []
    successful_experiments = 0
    attempts = 0
    MAX_ATTEMPTS = NUM_EXPERIMENTS_TARGET * 5000
    random.seed()
    while successful_experiments < NUM_EXPERIMENTS_TARGET and attempts < MAX_ATTEMPTS:
        attempts += 1
        p = random.randint(min_p, max_p)
        if p < 5 or p % 2 == 0:
            continue
        if USE_FILTER and not filter_miller_rabin(p, FILTER_ITERATIONS):
            continue
        factors = prime_factors(p - 1)
        if not factors and (p - 1) > 1:
            continue
        main_test_result = proverka_osnovnaya_s_faktorami(p, OSNOVNOY_TEST_BASES, factors)
        successful_experiments += 1
        experiment_numbers.append(successful_experiments)
        numbers_tested.append(p)
        results.append('+' if main_test_result else '-')
        iterations_used.append(OSNOVNOY_TEST_BASES)
        all_used_bases.append([])  # Базы не выводим подробно
    print("\n\nИтоговая таблица результатов ({} экспериментов):".format(successful_experiments))
    print("----------------------------------------------------------------------------------------------------")
    print("| {:<3} | {:<10} | {:<15} | {:<5} | {:<50} |".format("N", "P", "Результат (+/-)", "K", "Использованные базы 'a' (из основного теста)"))
    print("|-----|------------|-----------------|-------|----------------------------------------------------|")
    for i in range(len(experiment_numbers)):
        print("| {:<3} | {:<10} | {:<15} | {:<5} | {:<50} |".format(
            experiment_numbers[i], numbers_tested[i],
            "(+) Вероятно пр." if results[i] == '+' else "(-) Составное",
            iterations_used[i], "..."))
    print("----------------------------------------------------------------------------------------------------")
    print("* N     - номер успешного эксперимента.")
    print("* P     - число, проверенное основным тестом.")
    print("* (+/-) - результат основного теста (с использованием множителей P-1).")
    print("* K     - количество случайных оснований 'a', использованных в основном тесте (здесь = {} ).".format(OSNOVNOY_TEST_BASES))
    print("* Базы 'a' - список оснований, проверенных в основном тесте для данного P.")

if __name__ == "__main__":
    main()
