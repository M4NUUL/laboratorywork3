#include <iostream>
#include <vector>
#include "other_helpful_functions.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;
using ll = long long;
// Сито Эратосфена для поиска простых чисел
vector<int> sieve(int limit)
{
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}

// тест Миллера
bool millerTest(ll n, int t)
{
    if (n < 2)
        return false;
    int s = 0;
    int d = n - 1;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }
    for (int i = 0; i < t; i++)
    {
        int a = 2 + rand() % (n - 3);
        int x = powMod(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool continueLoop = false;
        for (int r = 1; r < s; r++)
        {
            x = powMod(x, 2, n);
            if (x == n - 1)
            {
                continueLoop = true;
                break;
            }
        }
        if (!continueLoop)
            return false;
    }
    return true;
}

// тест Поклингтона
bool poklingtonTest(int n, int F, vector<int> F_factors, int t)
{
    int R = (n - 1) / F;
    for (int i = 0; i < t; i++)
    {
        int a = 2 + rand() % (n - 3);
        if (powMod(a, n - 1, n) != 1)
            return false;
        bool found = true;
        for (int q : F_factors)
        {
            if (powMod(a, (n - 1) / q, n) == 1)
            {
                found = false;
                break;
            }
        }
        if (found)
            return true;
    }
    return false;
}

// тест ГОСТ
bool GOSTtest(int q, int t)
{
    int R = 2;
    while (true)
    {
        int n = q * R + 1;
        if (n >= (1 << t))
            break;
        int a = 2;
        if (powMod(a, n - 1, n) == 1 && powMod(a, (n - 1) / q, n) != 1)
        {
            return true;
        }
        R += 2;
    }
    return false;
}

// Генератор кандидата на простое число с помощью теста Миллера
int generateCandidateMiller(vector<int> &primes, int min_bits)
{
    while (true)
    {
        int m = 1;
        for (int i = 0; i < 3; ++i)
        {
            int q = primes[rand() % primes.size()];
            int alpha = 1 + rand() % 3;
            for (int j = 0; j < alpha; ++j)
                m *= q;
        }
        int n = 2 * m + 1;
        if (n >= (1 << (min_bits - 1)) && n < (1 << min_bits))
        {
            if (millerTest(n, 5)) // параметр надежности t = 5
                return n;
        }
    }
}

vector<ll> millerPrimes; // Вектор потенциально простых чисел

// Генератор кандидата на простое число с помощью теста Поклингтона
ll generateCandidatePocklington(const vector<int> &primes, int bit_size = 10)
{
    while (true)
    {
        ll F = 1;
        set<int> used;
        vector<int> F_factors;

        // выбираем 2-3 случайных простых числа для F
        while (F_factors.size() < 3)
        {
            int q = primes[rand() % primes.size()];
            if (used.count(q))
                continue;
            used.insert(q);
            F_factors.push_back(q);
            F *= q;
        }

        // берём R — случайное чётное число немного меньше F
        ll R = 2 * (1 + rand() % (F / 4 + 1));
        ll n = R * F + 1;

        // Проверка, что число нужной битовой длины
        if (n >= (1 << (bit_size - 1)) && n < (1 << bit_size))
        {
            if (poklingtonTest(n, F, F_factors, 5))
            {
                return n;
            }
        }
    }
}

// Генерация кандидатов на простые числа с помощью теста ГОСТ
ll generateCandidateGost(const vector<int> &primes, int t_bits = 10)
{
    int q_size = t_bits / 2; // ГОСТ требует, чтобы |q| ≈ t/2
    vector<int> q_candidates;
    for (int p : primes)
    {
        if ((1 << (q_size - 1)) <= p && p < (1 << q_size))
            q_candidates.push_back(p);
    }

    while (true)
    {
        int q = q_candidates[rand() % q_candidates.size()];
        int maxR = 4 * (q + 1);
        for (int R = 2; R < maxR; R += 2)
        {
            ll n = (ll)q * R + 1;
            if (n >= (1 << (t_bits - 1)) && n < (1 << t_bits))
            {
                if (GOSTtest(n, q))
                    return n;
            }
        }
    }
}

void runTestAndPrintTable(
    const string &methodName,
    const vector<ll> &candidates,
    bool (*testFunc)(ll, int),
    int t_initial = 5,
    int t_retry = 10)
{
    vector<TestResult> results;
    int k = 0;

    for (ll num : candidates)
    {
        bool passed = testFunc(num, t_initial);
        bool falseReject = false;

        if (!passed && testFunc(num, t_retry))
        {
            falseReject = true;
            k++;
        }

        results.push_back({num, passed, falseReject});
    }

    // Вывод таблицы
    cout << "\nРезультаты для метода: " << methodName << "\n";
    cout << "№\tP\t\tРезультат\tK\n";
    for (size_t i = 0; i < results.size(); ++i)
    {
        cout << i + 1 << "\t" << results[i].number << "\t\t"
             << (results[i].passed ? "+" : "-") << "\t\t"
             << (results[i].falseReject ? "1" : "0") << "\n";
    }
    cout << "Общее количество ложных отказов (k): " << k << "\n";
}

// Функция для генерации фиксированного кандидата на простое число по ГОСТ
ll generateGostFixed(int q, int t) {
    ll N = (1LL << (t - 1)) / q;

    if (N % 2 != 0) N++;  // если нечётное — делаем чётным

    ll u = 0;

    while (true) {
        ll p = (N + u) * q + 1;
        if (p >= (1LL << t)) break;  // не должен выходить за пределы 2^t

        if (powMod(2, p - 1, p) == 1 && powMod(2, (p - 1) / q, p) != 1)
            return p;

        u += 2;
    }

    return -1; // если не удалось найти
}

int main()
{
    vector<int> primes = sieve(500); // Простые числа, сгенерированные с помощью Сита Эратосфена ||
                                     // Для ГОСТ возможо придется использовать (1000)

    // Создание кандидатов на простые числа тестом Миллера
    while (millerPrimes.size() < 10)
    {
        int p = generateCandidateMiller(primes, 10); // например, 10-битное число
        millerPrimes.push_back(p);
    }

    // Создание кандидатов на простые числа тестом Поклингтона
    srand(time(0));
    vector<ll> generated;
    // Цикл для генерации 10 кандидатов
    for (int i = 0; i < 10; ++i)
    {
        ll candidate = generateCandidatePocklington(primes, 10);
        cout << "Pocklington Prime #" << i + 1 << ": " << candidate << endl;
        generated.push_back(candidate);
    }

    // Создание кандидатов на простые числа тестом ГОСТ
    vector<ll> gostPrimes;
    for (int i = 0; i < 10; ++i)
    {
        ll p = generateCandidateGost(primes, 10);
        cout << "GOST Prime #" << i + 1 << ": " << p << endl;
        gostPrimes.push_back(p);
    }

    // Запуск тестов и вывод результатов для кандидатов на простые числа
    runTestAndPrintTable("Miller", millerPrimes, millerTest);
    runTestAndPrintTable("Pocklington", generated, millerTest);
    runTestAndPrintTable("GOST", gostPrimes, millerTest);

    // Проверка составных чисел тестом Миллера (из таблицы в документации)
    vector<ll> compositeMiller = {335, 437, 657, 779, 1189, 1191, 1533, 1785, 2071};
    cout << "Проверка составных чисел тестом Миллера:\n";
    for (ll n : compositeMiller)
    {
        bool result = millerTest(n, 5);
        cout << n << "\t→ " << (result ? "[ОШИБКА: определено как простое]" : "составное") << "\n";
    }

    // Проверка составных чисел тестом Поклингтона (из таблицы в документации)
    vector<PockTestCase> compositePocklington = {
        {335, 167, {167}},        // R = 2
        {437, 109, {109}},        // R = 4
        {657, 41, {41}},          // R = 16
        {1189, 33 * 11, {3, 11}}, // R = 4
        // Добавь остальные
    };

    cout << "Проверка составных чисел тестом Поклингтона:\n";
    for (auto &test : compositePocklington)
    {
        bool result = poklingtonTest(test.n, test.F, test.F_factors, 5);
        cout << test.n << "\t→ " << (result ? "[ОШИБКА]" : "составное") << "\n";
    }

    // Проверка составных чисел тестом ГОСТ (из таблицы в документации)
    vector<GostTestCase> gostCases = {
        {3, 4, 13},
        {5, 6, 41},
        {11, 8, 199},
        {17, 10, 613}};

    cout << "Проверка генерации по ГОСТ (ξ=0):\n";
    for (auto &test : gostCases)
    {
        ll p = generateGostFixed(test.q, test.t); // Напиши версию generateCandidateGost без rand()
        cout << "Ожидалось: " << test.expected << ", Получено: " << p
             << (p == test.expected ? " [ОК]" : " [ОШИБКА]") << "\n";
    }
    return 0;
}
