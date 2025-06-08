#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <string.h>
#include <numeric>

using namespace std;

// Вычисляет наибольший общий делитель (НОД) двух чисел
long long gcd(long long n1, long long n2) {
    if (n1 < 0) n1 = -n1;
    if (n2 < 0) n2 = -n2;
    while (n2 != 0) {
        long long temp = n1 % n2;
        n1 = n2;
        n2 = temp;
    }
    return n1;
}

// Быстрое возведение в степень (целые числа)
long long power(long long base, int exp) {
    long long res = 1;
    if (exp == 0) return 1;
    if (base == 0) return 0;
    long long current_base = base;
    int current_exp = exp;
    while (current_exp > 0) {
        if (current_exp % 2 == 1) {
            res *= current_base;
        }
        current_exp /= 2;
        if (current_exp > 0) {
             current_base *= current_base;
        }
    }
    return res;
}

long long A[11][11];

// Динамическое вычисление чисел Эйлера для формулы суммы
void computeEulerian(int max_n) {
    memset(A, 0, sizeof(A));
    A[0][0] = 1;
    for (int n = 1; n <= max_n; ++n) {
        for (int k = 0; k < n; ++k) {
            long long term1 = 0;
            if (k > 0) {
                 term1 = (long long)(n - k) * A[n - 1][k - 1];
            }
            long long term2 = (long long)(k + 1) * A[n - 1][k];
            A[n][k] = term1 + term2;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b;
    if (!(cin >> a >> b)) {
         cerr << "Ошибка чтения ввода." << endl;
         return 1;
    }
    if (a < 1 || a > 10 || b < 1 || b > 10) {
         cerr << "Входные значения должны быть от 1 до 10." << endl;
         return 1;
    }
    // Если b == 1, ряд расходится
    if (b == 1) {
        cout << "бесконечность" << endl;
    }
    else {
        computeEulerian(a); // подготовка чисел Эйлера
        long long numerator = 0;
        // Считаем числитель по формуле с числами Эйлера
        for (int j = 0; j < a; ++j) {
            long long term_power = power(b, a - j);
            long long term_product = A[a][j] * term_power;
            numerator += term_product;
        }
        long long denominator = power(b - 1, a + 1);
        if (denominator <= 0) {
             cerr << "Внутренняя ошибка: Вычисление знаменателя не удалось или результат неположительный." << endl;
             return 1;
        }
        // Сокращаем дробь
        long long common = gcd(numerator, denominator);
        long long p = numerator / common;
        long long q = denominator / common;
        cout << p << "/" << q << endl;
    }
    return 0;
}
