import math
from math import gcd
import sys

def power(base, exp):
    res = 1
    while exp > 0:
        if exp % 2:
            res *= base
        base *= base
        exp //= 2
    return res

# Числа Эйлера
A = [[0 for _ in range(11)] for _ in range(11)]

def compute_eulerian(max_n):
    for i in range(11):
        for j in range(11):
            A[i][j] = 0
    A[0][0] = 1
    for n in range(1, max_n + 1):
        for k in range(n):
            term1 = (n - k) * A[n - 1][k - 1] if k > 0 else 0
            term2 = (k + 1) * A[n - 1][k]
            A[n][k] = term1 + term2

def main():
    a, b = map(int, input().split())
    if a < 1 or a > 10 or b < 1 or b > 10:
        print("Input values must be in [1, 10].", file=sys.stderr)
        return
    if b == 1:
        print("infinity")
        return
    compute_eulerian(a)
    num = 0
    for j in range(a):
        num += A[a][j] * power(b, a - j)
    denom = power(b - 1, a + 1)
    g = math.gcd(num, denom)
    print(f"{num // g}/{denom // g}")

if __name__ == "__main__":
    main()
