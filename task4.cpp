#include <iostream>
#include <vector>
#include <numeric>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    // Префиксные суммы для быстрого подсчёта сумм отрезков
    std::vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + a[i];
    }
    // dp[i] — максимальная разница очков, которую может получить текущий игрок, начиная с позиции i
    std::vector<long long> dp(n + 1);
    std::vector<long long> value(n + 1);
    std::deque<int> dq;
    dp[n] = 0;
    value[n] = prefix_sum[n] - dp[n];
    dq.push_back(n);
    for (int i = n - 1; i >= 0; --i) {
        // Поддерживаем окно [i+1, i+m]
        while (!dq.empty() && dq.front() > i + m) {
            dq.pop_front();
        }
        // Оптимальный ход — максимум value[j] в окне
        dp[i] = value[dq.front()] - prefix_sum[i];
        value[i] = prefix_sum[i] - dp[i];
        // Поддерживаем убывание value в деке
        while (!dq.empty() && value[dq.back()] <= value[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    // Если dp[0] > 0, первый игрок выигрывает
    cout << (dp[0] > 0 ? 1 : 0) << endl;
    return 0;
}
