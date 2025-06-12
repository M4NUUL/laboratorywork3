#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef uint64_t bint;

bint W;
const int N = 500;
vector<bool> resheto(N, true);
vector<int> simpleNums;

random_device rd;
mt19937 gen(rd());

int bit_length(bint x) {
    int bits = 0;
    while (x > 0) {
        x >>= 1;
        bits++;
    }
    return bits;
}

bint int_pow(bint base, int exp) {
    bint result = 1;
    for (int i = 0; i < exp; ++i) {
        if (result > UINT64_MAX / base) return 0;
        result *= base;
    }
    return result;
}

bint mod_pow(bint a, bint x, bint m) {
    bint result = 1;
    a %= m;
    while (x > 0) {
        if (x & 1) {
            result = ((__int128)result * a ) % m;
        }
        a = ((__int128)a * a ) % m;
        x >>= 1;
    }
    return result;
}

bool millerRabin(bint n, int t) {
    if (n < 2) return false;
    bint d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    uniform_int_distribution<bint> dist(2, n - 2);
    for (int i = 0; i < t; i++) {
        bint a = dist(gen);
        bint x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = ((__int128)x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

void eratosfen() {
    resheto[0] = resheto[1] = false;
    for (int i = 2; i * i < N; ++i) {
        if (resheto[i]) {
            for (int j = i * i; j < N; j += i)
                resheto[j] = false;
        }
    }
    for (int i = 2; i < N; i++) {
        if (resheto[i]) {
            simpleNums.push_back(i);
        }
    }
}

vector<bint> millerOtbros;

bool millerTest(bint n, int t, const vector<int>& qs) {
    uniform_int_distribution<bint> dis(2, n-1);
    vector<bint> randomBint;
    for (int i = 0; i < t; i++) {
        bint elem;
        do {
            elem = dis(gen);
        } while (find(randomBint.begin(), randomBint.end(), elem) != randomBint.end());
        if (mod_pow(elem, n-1, n) != 1) {
            return false;
        }
        randomBint.push_back(elem);
    }
    for (const auto& qi : qs) {
        bool f = false;
        for (const auto& aj : randomBint) {
            bint res = mod_pow(aj, ((n-1)/qi), n);
            if (res != 1) {
                f = true;
                break;
            }
        }
        if (!f) return false;
    }
    return true;
}

pair<bint, vector<int>> millerGen(int k) {
    bint m = 1;
    uniform_int_distribution<> dis(0, simpleNums.size() - 1);
    uniform_int_distribution<> dis2(1, 3);
    vector<int> qs;
    do {
        qs.clear();
        m = 1;
        for (int i = 0; i < k; i++) {
            int q = simpleNums[dis(gen)];
            qs.push_back(q);
            int a = dis2(gen);
            bint elem = int_pow(q, a);
            if (elem == 0 || bit_length(m) + bit_length(elem) > (W - 1)) {
                m = 0;
                break;
            }
            m *= elem;
        }
    } while (bit_length(m) != (W - 1) || m == 0);
    qs.push_back(2);
    sort(qs.begin(), qs.end());
    qs.erase(unique(qs.begin(), qs.end()), qs.end());
    bint n = 2 * m + 1;
    return {n, qs};
}

bint miller(int k, int t) {
    bint final;
    while (true) {
        auto [n, qs] = millerGen(k);
        final = n;
        if (millerTest(n, t, qs)) break;
        else millerOtbros.push_back(n);
    }
    return final;
}

vector<bint> polingtonOtbros;

bool polingtonTest(bint n, int t, const vector<int>& qs) {
    uniform_int_distribution<bint> dis(2, n-1);
    vector<bint> randomBint;
    for (int i = 0; i < t; i++) {
        bint elem;
        do {
            elem = dis(gen);
        } while (find(randomBint.begin(), randomBint.end(), elem) != randomBint.end());
        if (mod_pow(elem, n-1, n) != 1) {
            return false;
        }
        randomBint.push_back(elem);
    }
    for (const auto& aj : randomBint) {
        bool f = false;
        for (const auto& qi : qs) {
            bint res = mod_pow(aj, ((n-1)/qi), n);
            if (res == 1) {
                f = true;
                break;
            }
        }
        if (!f) return true;
    }
    return false;
}

pair<bint, vector<int>> polingtonGen(int k) {
    bint F = 1;
    uniform_int_distribution<> dis(0, simpleNums.size() - 1);
    uniform_int_distribution<> dis2(1, 3);
    uniform_int_distribution<bint> dis3(2, pow(2, W));
    vector<int> qs;
    do {
        qs.clear();
        F = 1;
        for (int i = 0; i < k; i++) {
            int q = simpleNums[dis(gen)];
            qs.push_back(q);
            int a = dis2(gen);
            bint elem = int_pow(q, a);
            if (elem == 0 || bit_length(F) + bit_length(elem) > (W/2)) {
                F = 0;
                break;
            }
            F *= elem;
        }
    } while (bit_length(F) != (W/2-1) || F == 0);
    qs.push_back(2);
    sort(qs.begin(), qs.end());
    qs.erase(unique(qs.begin(), qs.end()), qs.end());
    bint R;
    while (true) {
        bint a = dis3(gen);
        if (a % 2 == 0 && W - bit_length(F) == bit_length(a)) {
            R = a;
            break;
        }
    }
    bint n = R * F + 1;
    return {n, qs};
}

bint polington(int k, int t) {
    bint final;
    while (true) {
        auto [n, qs] = polingtonGen(k);
        final = n;
        if (polingtonTest(n, t, qs)) break;
        else polingtonOtbros.push_back(n);
    }
    return final;
}

vector<bint> gostOtbros;

bint gost(int q, int t, int c_flag) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    while (true) {
        double xi = dist(gen);
        if (c_flag == 0) xi = 0;
        double A = ceil(pow(2.0, t - 1) / (double)q);
        double B = ceil(pow(2.0, t - 1) * xi / (double)q);
        bint N = (bint)A + (bint)B;
        if (N % 2 == 1) N++;
        int u = 0;
        while (true) {
            bint p = (N + u) * q + 1;
            if (p > (bint)1 << t) break;
            if (mod_pow(2, p - 1, p) == 1 && mod_pow(2, N + u, p) != 1) {
                return p;
            }
            gostOtbros.push_back(p);
            u += 2;
        }
    }
}

// ======== ИЗМЕНЁННАЯ ЧАСТЬ ========
void tables() {
    vector<bint> millerGens, polingtonGens, gostGens;
    vector<vector<bint>> millerSost, polingtonSost, gostSost;

    for (int i = 0; i < 10; i++) {
        millerOtbros.clear();
        millerGens.push_back(miller(3, 5));
        millerSost.push_back(millerOtbros);
    }

    cout << "\nТаблица для метода Миллера\n";
    cout << left << setw(5) << "№" << setw(25) << "P" << setw(5) << "Rs" << setw(5) << "K" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < 10; ++i) {
        int k = 0;
        for (const auto& j : millerSost[i])
            if (millerRabin(j, 2)) k++;
        cout << left << setw(5) << (i + 1)
             << setw(25) << millerGens[i]
             << setw(5) << (millerRabin(millerGens[i], 2) ? "+" : "-")
             << setw(5) << k << endl;
    }

    for (int i = 0; i < 10; i++) {
        polingtonOtbros.clear();
        polingtonGens.push_back(polington(3, 5));
        polingtonSost.push_back(polingtonOtbros);
    }

    cout << "\nТаблица для метода Полингтона\n";
    cout << left << setw(5) << "№" << setw(25) << "P" << setw(5) << "Rs" << setw(5) << "K" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < 10; ++i) {
        int k = 0;
        for (const auto& j : polingtonSost[i])
            if (millerRabin(j, 2)) k++;
        cout << left << setw(5) << (i + 1)
             << setw(25) << polingtonGens[i]
             << setw(5) << (millerRabin(polingtonGens[i], 2) ? "+" : "-")
             << setw(5) << k << endl;
    }

    for (int i = 0; i < 10; i++) {
        gostOtbros.clear();
        gostGens.push_back(gost(7, W, 1));
        gostSost.push_back(gostOtbros);
    }

    cout << "\nТаблица для метода по ГОСТ\n";
    cout << left << setw(5) << "№" << setw(25) << "P" << setw(5) << "Rs" << setw(5) << "K" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < 10; ++i) {
        int k = 0;
        for (const auto& j : gostSost[i])
            if (millerRabin(j, 2)) k++;
        cout << left << setw(5) << (i + 1)
             << setw(25) << gostGens[i]
             << setw(5) << (millerRabin(gostGens[i], 2) ? "+" : "-")
             << setw(5) << k << endl;
    }
}

void finaltest() {
    cout << "Желаете проверить корректность алгоритмов на данных из приложения? (1 - Да, 2 - Нет)\n";
    int cmd;
    cin >> cmd;
    if (cmd == 1) {
        // Тестовые функции при необходимости
    }
}

int main() {
    eratosfen();
    cout << "Введите требуемую битность чисел > ";
    cin >> W;
    tables();
    finaltest();
    return 0;
}
