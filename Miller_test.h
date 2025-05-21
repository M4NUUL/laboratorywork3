
#include <cstdint>   // uint64_t
#include <random>    // mt19937_64, uniform_int_distribution
#include <chrono>    // high_resolution_clock
#include <stdexcept> // для std::invalid_argument

namespace std {

    // Быстрое возведение в степень по модулю: a^d mod n
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

    // Тест Миллера–Рабина:
    // Вернёт true, если n — вероятно простое; иначе false.
    // t — количество раундов (по умолчанию 5), ошибка ≤ 1 / 4^t
    inline bool miller_test(uint64_t n, int t = 5) {
        if (n < 2)
            return false;
        if (n == 2 || n == 3)
            return true;
        if (n % 2 == 0)
            return false;

        // n - 1 = 2^s * d
        uint64_t d = n - 1;
        int s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            ++s;
        }

        mt19937_64 rng(
            chrono::high_resolution_clock::now().time_since_epoch().count()
        );
        uniform_int_distribution<uint64_t> dist(2, n - 2);

        for (int i = 0; i < t; ++i) {
            uint64_t a = dist(rng);
            uint64_t x = mod_pow(a, d, n);
            if (x == 1 || x == n - 1)
                continue;

            bool passed = false;
            for (int r = 1; r < s; ++r) {
                x = (__uint128_t)x * x % n;
                if (x == n - 1) {
                    passed = true;
                    break;
                }
            }
            if (!passed)
                return false;
        }
        return true;
    }

}