#include <iostream>
#include <vector>
#include "other_helpful_functions.h"
using namespace std;

//Сито Эратосфена для поиска простых чисел
vector<int> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}

//тест Миллера
bool millerTest(int n, int t) {
    if (n < 2) return false;
    int s = 0;
    int d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (int i = 0; i < t; i++) {
        int a = 2 + rand() % (n - 3);
        int x = powMod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool continueLoop = false;
        for (int r = 1; r < s; r++) {
            x = powMod(x, 2, n);
            if (x == n - 1) {
                continueLoop = true;
                break;
            }
        }
        if (!continueLoop) return false;
    }
    return true;
}


//тест Поклингтона
bool poklingtonTest(int n, int F, vector<int> F_factors, int t) {
    int R = (n - 1) / F;
    for (int i = 0; i < t; i++) {
        int a = 2 + rand() % (n - 3);
        if (powMod(a, n - 1, n) != 1) return false;
        bool found = true;
        for (int q : F_factors) {
            if (powMod(a, (n - 1) / q, n) == 1) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }
    return false;
}

//тест ГОСТ
bool GOSTtest(int q, int t) {
    int R = 2;
    while (true) {
        int n = q * R + 1;
        if (n >= (1 << t)) break;
        int a = 2;
        if (powMod(a, n - 1, n) == 1 && powMod(a, (n - 1) / q, n) != 1) {
            return true;
        }
        R += 2;
    }
    return false;
}

vector<int> primes = sieve(500);
