#include <vector>
using namespace std;
using ll = long long;
// Возведение a в степень b по модулю m
int powMod(int a, int b, int m)
{
    int result = 1;
    a = a % m; // на случай, если a >= m
    while (b > 0)
    {
        if (b % 2 == 1)
            result = (1LL * result * a) % m; // 1LL для предотвращения переполнения
        a = (1LL * a * a) % m;
        b /= 2;
    }
    return result;
}


// Структура для хранения результатов тестов
struct TestResult {
    ll number;     // число
    bool passed;   // результат первого прогона
    bool falseReject; // был ли ложный отказ
};

// Структура для теста Поклингтона со значениями из таблицы 
struct PockTestCase {
    ll n;             // Число
    ll F;
    vector<int> F_factors;
};

// Структура для хранения результатов тестов ГОСТ
struct GostTestCase {
    int q;
    int t;
    ll expected;
};