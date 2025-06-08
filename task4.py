def main():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    prefix_sum = [0] * (n + 1)
    for i in range(n):
        prefix_sum[i + 1] = prefix_sum[i] + a[i]
    dp = [0] * (n + 1)
    value = [0] * (n + 1)
    dq = []
    dp[n] = 0
    value[n] = prefix_sum[n] - dp[n]
    dq.append(n)
    for i in range(n - 1, -1, -1):
        while dq and dq[0] > i + m:
            dq.pop(0)
        dp[i] = value[dq[0]] - prefix_sum[i]
        value[i] = prefix_sum[i] - dp[i]
        while dq and value[dq[-1]] <= value[i]:
            dq.pop()
        dq.append(i)
    print(1 if dp[0] > 0 else 0)

if __name__ == "__main__":
    main()
