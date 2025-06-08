def gcd(n1, n2):
    n1 = abs(n1)
    n2 = abs(n2)
    while n2 != 0:
        n1, n2 = n2, n1 % n2
    return n1

def power(base, exp):
    res = 1
    if exp == 0:
        return 1
    if base == 0:
        return 0
    current_base = base
    current_exp = exp
    while current_exp > 0:
        if current_exp % 2 == 1:
            res *= current_base
        current_exp //= 2
        if current_exp > 0:
            current_base *= current_base
    return res

def compute_eulerian(max_n):
    A = [[0] * 11 for _ in range(11)]
    A[0][0] = 1
    for n in range(1, max_n + 1):
        for k in range(n):
            term1 = (n - k) * A[n - 1][k - 1] if k > 0 else 0
            term2 = (k + 1) * A[n - 1][k]
            A[n][k] = term1 + term2
    return A

def main():
    try:
        a, b = map(int, input().split())
    except Exception:
        print("Ошибка чтения ввода.")
        return
    if not (1 <= a <= 10 and 1 <= b <= 10):
        print("Входные значения должны быть от 1 до 10.")
        return
    if b == 1:
        print("бесконечность")
        return
    A = compute_eulerian(a)
    numerator = 0
    for j in range(a):
        term_power = power(b, a - j)
        term_product = A[a][j] * term_power
        numerator += term_product
    denominator = power(b - 1, a + 1)
    if denominator <= 0:
        print("Внутренняя ошибка: Вычисление знаменателя не удалось или результат неположительный.")
        return
    common = gcd(numerator, denominator)
    p = numerator // common
    q = denominator // common
    print(f"{p}/{q}")

if __name__ == "__main__":
    main()
