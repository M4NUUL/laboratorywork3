import random

def main():
    n, m = map(int, input("Введите N и M через пробел: ").split())
    chisla = []

    if n < 0:
        n = abs(n)
        for i in range(n):
            chisla.append(random.randint(5, 50000))
        print("Случайно сгенерированный список:", chisla)
    else:
        for i in range(n):
            z = int(input(f"Введите число №{i+1} > "))
            chisla.append(z)

    dp = [0] * (n + 1)
    dp[n] = 0
    for i in range(n - 1, -1, -1):
        dp[i] = -2147483648
        sum = 0
        for k in range(1, m + 1):
            if i + k <= n:
                sum += chisla[i + k - 1]
                dp[i] = max(dp[i], sum - dp[i + k])

    print(1 if dp[0] > 0 else 0)

if __name__ == "__main__":
    main()