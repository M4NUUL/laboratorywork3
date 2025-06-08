import random
import math
from collections import Counter

def pow_mod(base, exponent, mod):
    result = 1
    base %= mod
    while exponent > 0:
        if exponent & 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exponent >>= 1
    return result

def rand_int(minv, maxv):
    return random.randint(minv, maxv)

def rand_double():
    return random.random()

def sieve_eratos(N):
    is_prime = [True] * (N + 1)
    primes = []
    for p in range(2, N + 1):
        if is_prime[p]:
            primes.append(p)
            for i in range(p * 2, N + 1, p):
                is_prime[i] = False
    return primes

def miller_rabin(n, iterations=5):
    if n < 2 or n % 2 == 0:
        return False
    d = n - 1
    r = 0
    while d % 2 == 0:
        d //= 2
        r += 1
    for _ in range(iterations):
        a = rand_int(2, n - 2)
        x = pow_mod(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow_mod(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

def generate_gost_prime(primes, bit_len):
    q_bit_len = (bit_len + 1) // 2
    q_min = 0
    q_max = (1 << q_bit_len) - 1
    q = 0
    while True:
        q = primes[rand_int(0, len(primes) - 1)]
        if q_min <= q <= q_max:
            break
    while True:
        xi = rand_double()
        n = (1 << (bit_len - 1)) + (xi * (1 << (bit_len - 1)))
        n_int = int(n // q)
        if n_int % 2 != 0:
            n_int += 1
        k = 0
        while True:
            p = (n_int + k) * q + 1
            if p >= (1 << bit_len):
                break
            if pow_mod(2, p - 1, p) == 1 and pow_mod(2, n_int + k, p) != 1:
                return p
            k += 2

def main():
    bit_length = 12
    test_rounds = 5
    primes_set = set()
    primes = sieve_eratos(500)
    test_results = []
    while len(primes_set) < 10:
        p = generate_gost_prime(primes, bit_length)
        if p in primes_set:
            continue
        if miller_rabin(p, test_rounds):
            primes_set.add(p)
            test_results.append("ПРОЙДЕН")
    print("╔═════╦═══════╦═══════════════════════╗")
    print("║  №  ║   P   ║ Тест Миллера-Рабина   ║")
    print("╠═════╬═══════╬═══════════════════════╣")
    for i, p in enumerate(primes_set, 1):
        print(f"║ {i:3d} ║ {p:5d} ║{'ПРОЙДЕН':>21}         ║")
    print("╚═════╩═══════╩═══════════════════════╝")

if __name__ == "__main__":
    main()
