import math

def sokr(chisl, znam):
    g = math.gcd(chisl, znam)
    return str(chisl // g) + "/" + str(znam // g)

def calc_sum(a, b):
    if b == 1:
        return "infinity"

    if a == 1:
        znam = (b - 1) * (b - 1)
        return sokr(b, znam)

    if a == 2:
        chisl = b * (b + 1)
        znam = (b - 1) * (b - 1) * (b - 1)
        return sokr(chisl, znam)

    sum = 0.0
    max_terms = 10000
    prev_sum = 0.0
    converged = False

    for n in range(1, max_terms + 1):
        sum += n**a / (b**n)
        if abs(sum - prev_sum) < 1e-10:
            converged = True
            break
        prev_sum = sum

    if not converged:
        return "irrational"

    if abs(sum - round(sum)) < 1e-10:
        return str(int(round(sum))) + "/1"

    for denom in range(2, 1001):
        numerator = sum * denom
        if abs(numerator - round(numerator)) < 1e-10:
            return sokr(int(round(numerator)), denom)

    return "irrational"

def main():
    print("Введите значения a и b через пробел: ")
    while True:
        a, b = map(int, input().split())
        if a < 1 or a > 10 or b < 1 or b > 10:
            print("Числа должны быть в диапазоне от 1 до 10!")
        else: break        

    print("Результат:", calc_sum(a, b))

if __name__ == "__main__":
    main()