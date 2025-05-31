from collections import deque

def main():
    n, m = map(int, input().split())
    numbers = list(map(int, input().split()))

    prefix = [0] * (n + 1)
    for i in range(n):
        prefix[i + 1] = prefix[i] + numbers[i]

    dp = [0] * (n + 1)
    value = [0] * (n + 1)
    dq = deque()

    dp[n] = 0
    value[n] = prefix[n]
    dq.append(n)

    for i in range(n - 1, -1, -1):
        # Удаляем устаревшие индексы из окна [i+1, i+m]
        while dq and dq[0] > i + m:
            dq.popleft()
        # Выбираем лучший ход
        dp[i] = value[dq[0]] - prefix[i]
        value[i] = prefix[i] - dp[i]
        # Поддерживаем убывающий порядок в dq
        while dq and value[dq[-1]] <= value[i]:
            dq.pop()
        dq.append(i)

    print(1 if dp[0] > 0 else 0)

if __name__ == "__main__":
    main()
