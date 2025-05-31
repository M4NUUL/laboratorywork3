#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    // Префиксные суммы: prefix[i] — сумма первых i чисел
    vector<long long> prefix(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + numbers[i];
    }

    vector<long long> dp(n + 1);      // dp[i] — макс. разница (свои - чужие очки), начиная с позиции i
    vector<long long> value(n + 1);   // value[i] = prefix[i] - dp[i]

    deque<int> dq;

    dp[n] = 0;
    value[n] = prefix[n];
    dq.push_back(n);

    for (int i = n - 1; i >= 0; --i) {
        // Удаляем устаревшие индексы из окна [i+1, i+m]
        while (!dq.empty() && dq.front() > i + m) {
            dq.pop_front();
        }

        // Выбираем лучший ход
        dp[i] = value[dq.front()] - prefix[i];
        value[i] = prefix[i] - dp[i];

        // Поддерживаем убывающий порядок в dq
        while (!dq.empty() && value[dq.back()] <= value[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    cout << (dp[0] > 0 ? 1 : 0) << '\n';
    return 0;
}
