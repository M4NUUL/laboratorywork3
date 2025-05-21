
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>
#include <numeric> // std::gcd (C++17)
#include <stdexcept>

namespace std {

    // Быстрое возведение в степень по модулю
    inline uint64_t mod_pow(uint64_t a, uint64_t d, uint64_t n) {
        uint64_t result = 1;
        a %= n;
        while (d > 0) {
            if (d & 1)
                result = (__uint128_t)result * a % n;
            a = (__uint128_t)a * a % n;
            d >>= 1;
        }
        return result;
    }

    // Тест Поклингтона:
    // n — проверяемое число
    // factors — известные простые делители F, такой что n-1 = F * R
    // t — число попыток
    inline bool pocklington_test(uint64_t n, const vector<uint64_t>& factors, int t = 5) {
        if (n < 2 || n % 2 == 0)
            return false;

        // Вычисляем F и R из факторизации
        uint64_t F = 1;
        for (uint64_t q : factors) {
            F *= q;
        }
        if ((n - 1) % F != 0)
            throw invalid_argument("n - 1 не делится на F");

        uint64_t R = (n - 1) / F;

        mt19937_64 rng(
            chrono::high_resolution_clock::now().time_since_epoch().count()
        );
        uniform_int_distribution<uint64_t> dist(2, n - 2);

        for (int i = 0; i < t; ++i) {
            uint64_t a = dist(rng);

            if (mod_pow(a, n - 1, n) != 1)
                continue; // не проходит первое условие

            bool passes = true;
            for (uint64_t q : factors) {
                uint64_t exp = (n - 1) / q;
                uint64_t res = mod_pow(a, exp, n);
                if (gcd(res - 1, n) != 1) {
                    passes = false;
                    break;
                }
            }
            if (passes)
                return true; // Найдено подходящее a ⇒ n точно простое
        }

        return false; // После t попыток ничего не найдено ⇒ вероятно составное
    }

} 