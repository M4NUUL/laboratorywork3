
#include <cstdint>
#include <stdexcept>
#include <numeric>  // для std::gcd
#include <chrono>
#include <random>

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

    // Тест на простоту по ГОСТ Р 34.10-94 (теорема Диемитко)
    // n = q * R + 1, где q — простой, R — чётное
    inline bool diem_test(uint64_t n, uint64_t q, uint64_t R, uint64_t a = 2) {
        // Проверка условий: R чётное, n = q * R + 1
        if (n < 2 || q < 2 || R % 2 != 0 || q * R + 1 != n)
            return false;

        // Условие 1: a^(n-1) ≡ 1 mod n
        if (mod_pow(a, n - 1, n) != 1)
            return false;

        // Условие 2: gcd(a^R - 1, n) == 1
        uint64_t ar = mod_pow(a, R, n);
        if (gcd(ar - 1, n) != 1)
            return false;

        // Оба условия выполнены
        return true;
    }

}