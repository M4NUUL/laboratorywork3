import random
from math import gcd

def pow_mod(base, degree, mod):
    result = base % mod
    for _ in range(2, degree + 1):
        result = (result * base) % mod
    return result

def sieve_eratos(N):
    bool_prime = [True] * (N + 1)
    for p in range(2, int(N ** 0.5) + 1):
        if bool_prime[p]:
            for i in range(p * p, N + 1, p):
                bool_prime[i] = False
    return [p for p in range(2, N + 1) if bool_prime[p]]

def rabin(num, k):
    if num == 2 or num == 3:
        return True
    if num < 2 or num % 2 == 0:
        return False
    s = 0
    d = num - 1
    while d % 2 == 0:
        d //= 2
        s += 1
    for _ in range(k):
        a = random.randint(2, num - 2)
        x = pow_mod(a, d, num)
        y = None
        for _ in range(s):
            y = pow_mod(x, 2, num)
            if y == 1 and x != 1 and x != num - 1:
                return False
            x = y
        if y != 1:
            return False
    return True

def rand_dist(minv, maxv):
    return random.randint(minv, maxv)

def poklington(n, t, q_list):
    a_set = set()
    while len(a_set) != t:
        aj = rand_dist(2, n - 1)
        a_set.add(aj)
    for aj in a_set:
        if pow_mod(aj, n - 1, n) != 1:
            return False
    for aj in a_set:
        all_nol = True
        for qi in q_list:
            if pow_mod(aj, (n - 1) // qi, n) == 1:
                all_nol = False
                break
        if all_nol:
            return True
    return False

def calcN(prime, bit):
    max_index = len(prime) - 1
    max_pow = 1
    minv = bit // 2 + 1
    maxv = bit // 2 + 2
    pow_max = 2 ** maxv
    while 2 ** max_pow < 2 ** (bit // 2 + 1):
        max_pow += 1
    f = 1
    q_list = []
    while True:
        num = rand_dist(0, max_index)
        power = rand_dist(1, max_pow)
        if pow(prime[num], power):
            if f * pow(prime[num], power) < pow_max:
                f *= pow(prime[num], power)
                q_list.append(prime[num])
        if f > 2 ** (bit // 2):
            if f >= 2 ** (bit // 2 + 1):
                f = 1
                q_list.clear()
            else:
                break
    R = rand_dist(minv - 1, maxv - 1)
    if R % 2 != 0:
        R += 1
    n = R * f + 1
    return n, q_list

def main():
    bit = 10
    t = 10
    prime = sieve_eratos(500)
    result = []
    test_ver = []
    k_cont = []
    k = 0
    while len(result) < 10:
        n, q_list = calcN(prime, bit)
        if poklington(n, t, q_list):
            result.append(n)
            if rabin(n, 3):
                test_ver.append("+")
            else:
                test_ver.append("-")
            k_cont.append(k)
            k = 0
        else:
            if rabin(n, 3):
                k += 1
    print("\n╔" + "═"*143 + "╗")
    print("║Num\t║" + ''.join(f"\t{i}\t║" for i in range(1, 11)))
    print("╠" + "═"*143 + "╣")
    print("║P\t║" + '\t'.join(str(x) for x in result) + '\t║')
    print("║Test\t║" + '\t'.join(test_ver) + '\t║')
    print("║k\t║" + '\t'.join(str(x) for x in k_cont) + '\t║')
    print("╚" + "═"*143 + "╝")

if __name__ == "__main__":
    main()
