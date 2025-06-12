#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <algorithm>
#include <map>
#include <iomanip>

//добавить задавание битности числа
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
        if (result > UINT64_MAX / base) return 0; // переполнение
        result *= base;
    }
    return result;
}

bint mod_pow(bint a, bint x, bint m) {
    bint result = 1;
    a %= m;
    while (x > 0) {
        if (x & 1) {
            result = ((uint64_t)result * a ) % m;
        }
        a = ( (uint64_t)a * a ) % m;
        x >>= 1;
    }
    return result;
}

bool millerRabin(bint n, int t) {
    if (n < 2) return false;
    // найти d и s такие, что n-1 = 2^s * d, d нечётно
    bint d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    // t раз выбираем случайную a [2..n-2]:
    uniform_int_distribution<bint> dist(2, n - 2);
    for (int i = 0; i < t; i++) {
        bint a = dist(gen);
        bint x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = ( (uint64_t)x * x ) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false; 
    }
    return true;
}

//РЕШЕТО ЭРАТОСФЕНА
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

//МИЛЛЕР
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
        if (!f) {return false;}
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
            if (elem == 0 || bit_length(m) + bit_length(elem) > (W-1)) {
                m = 0;
                break;
            }
            m *= elem;
        }
    } while (bit_length(m) != (W-1) || m == 0);
    qs.push_back(2);

    sort(qs.begin(), qs.end());
    qs.erase(unique(qs.begin(), qs.end()), qs.end());


    bint n = 2*m + 1;
    return {n, qs};
}

bint miller(int k, int t) {
    bint final;
    while (true) {
        auto [n, qs] = millerGen(k);
        final = n;
        if (millerTest(n, t, qs)) {break;} else {millerOtbros.push_back(n);}
    }
    return final;
}

void TestAlgMiller() {
    map<int, vector<int>> tests = {
        {13, {2, 3}},
        {29, {2, 7}},
        {61, {2, 3, 5}},
        {97, {2, 3}},
        {157, {2, 13}},
        {173, {2, 43}},
        {179, {2, 89}},
        {353, {2, 11}},
        {419, {2, 11, 19}},
        {461, {2, 5, 23}},
        {617, {2, 7, 11}},
        {821, {2, 5, 41}},
        {1069, {2, 3, 89}},
        {5953, {2, 3, 31}},
        {6121, {2, 3, 5, 17}},
        {6197, {2, 1549}},
        {6373, {2, 3, 59}},
        //эти всегда отвергаются
        {335, {2, 167}},
        {437, {2, 109}},
        {657, {2, 41}},
        {779, {2, 389}},
        {1189, {2, 3, 11}},
        {1191, {2, 5, 7, 17}},
        {1533, {2, 383}},
        {1785, {2, 223}},
        {2071, {2, 3, 5, 23}},
        {2327, {2, 1163}},
        {2249, {2, 281}},
        {3057, {2, 191}},
        {3379, {2, 3, 563}},
        {4009, {2, 3, 167}},
        {4647, {2, 23, 101}},
        {5007, {2, 2503}},
        {5211, {2, 5, 521}},
        {8891, {2, 5, 7, 127}},
        {9451, {2, 3, 5, 7}},
        {9837, {2, 2459}},
        {9943, {2, 3, 1657}},
        {6141, {2, 5, 307}},
        {6259, {2, 3, 7, 149}},
        {6951, {2, 5, 139}},
        {7157, {2, 1789}},
        {7483, {2, 3, 29, 43}}
    };
    for (const auto& [n, qs] : tests) {
        double c = 0;
        for (int i = 0; i < 1000; i++) {
            if (!millerTest(n, 1, qs)) {c += 1;}
        }
        cout << n << " " << c/1000 << endl;
    }
}

//ПОЛИНГТОН
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
        if (!f) {return true;}
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
        if (polingtonTest(n, t, qs)) {break;} else {polingtonOtbros.push_back(n);}
    }
    return final;
}

void TestAlgPolington() {
    map<int, vector<int>> tests = {
        {13, {2}},
        {29, {7}},
        {61, {3, 5}},
        {97, {3, 2}},
        {157, {13}},
        {173, {43}},
        {179, {89}},
        {353, {2, 11}},
        {419, {11, 19}},
        {461, {23}},
        {617, {7, 11}},
        {821, {41}},
        {1069, {89}},
        {5953, {3, 31}},
        {6121, {5, 17}},
        {6197, {1549}},
        {6373, {3, 59}},
        //эти всегда отвергаются
        {335, {167}},
        {437, {109}},
        {657, {41}},
        {779, {389}},
        {1189, {3, 11}},
        {1191, {7, 17}},
        {1533, {383}},
        {1785, {223}},
        {2071, {5, 23}},
        {2327, {1163}},
        {2249, {281}},
        {3057, {191}},
        {3379, {563}},
        {4009, {167}},
        {4647, {101}},
        {5007, {2503}},
        {5211, {521}},
        {8891, {127}},
        {9451, {5, 7}},
        {9837, {2459}},
        {9943, {1657}},
        {6141, {307}},
        {6259, {149}},
        {6951, {139}},
        {7157, {1789}},
        {7483, {29, 43}}
    };
    for (const auto& [n, qs] : tests) {
        double c = 0;
        for (int i = 0; i < 1000; i++) {
            if (!polingtonTest(n, 1, qs)) {c += 1;}
        }
        cout << n << " " << c/1000 << endl;
    }
}

//ГОСТ
vector<bint> gostOtbros;

bint gost(int q, int t, int c_flag) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    
    while (true) {
        double xi = dist(gen);
        if (c_flag == 0) {xi = 0;}
        double A = ceil(pow(2.0, t-1) / (double)q );
        double B = ceil(pow(2.0, t-1) * xi / (double)q );
        bint N = (bint)A + (bint)B;
        if (N % 2 == 1) N++;

        int u = 0;
        while (true) {
            bint p = (N + u) * q + 1;
            if (p > (bint)1 << t) {break;}
            if (mod_pow(2, p-1, p) == 1 && mod_pow(2, N+u, p) != 1) {
                return p;
            }
            gostOtbros.push_back(p);
            u += 2;
        }
    }
}

void TestAlgGost() {
    vector<pair<int, pair<int, int>>> tests {
        {13, {3,4}},
        {41, {5,6}},
        {29, {7,5}},
        {31, {5,5}},
        {67, {11,7}},
        {199, {11,8}},
        {79, {13,7}},
        {131, {13,8}},
        {307, {17,9}},
        {613, {17,10}},
        {419, {19,9}},
        {277, {23,9}},
        {349, {29,9}},
        {311, {31,9}},
        {2221, {37,11}},
        {2297, {41,11}},
        {571, {19,10}},
        {599, {23,10}}
    };
    for (const auto& [f, c] : tests) {
        auto [q, t] = c;
        bint gostres = gost(q, t, 0);
        cout << q << " " << t << " " << gostres << (gostres == f ? " = " : " != ") << f << endl;
    }
}

//ВЫВОД ТАБЛИЦ
void tables() {
    //================================ТЕСТЫ НА МИЛЛЕРА
    vector<bint> millerGens;
    vector<vector<bint>> millerSost;
    for (int i = 0; i < 10; i++) {
        millerOtbros.clear();
        millerGens.push_back(miller(3, 5));
        millerSost.push_back(millerOtbros);
    }
    cout << "Таблица для метода Миллера\n";
    cout << "№  " << setw(8) << "P" << setw(25) << "Rs" << setw(6) << "K" << endl;
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        cout << left << setw(4) << (i+1)
             << left << setw(25) << millerGens[i]
             << left << setw(6) << (millerRabin(millerGens[i], 2) ? "+" : "-")
             << left << setw(6);
        int c = 0;
        for (const auto& j : millerSost[i]) {
            if (millerRabin(j, 2)) c++;
        }
        cout << c << endl;
    }
    cout << endl;    

    //================================ТЕСТЫ НА ПОЛИНГТОНА
    vector<bint> polingtonGens;
    vector<vector<bint>> polingtonSost;
    for (int i = 0; i < 10; i++) {
        polingtonOtbros.clear();
        polingtonGens.push_back(polington(3, 5));
        polingtonSost.push_back(polingtonOtbros);
    }
    cout << "Таблица для метода Полингтона\n";
    cout << "№  " << setw(8) << "P" << setw(25) << "Rs" << setw(6) << "K" << endl;
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        cout << left << setw(4) << (i+1)
             << left << setw(25) << polingtonGens[i]
             << left << setw(6) << (millerRabin(polingtonGens[i], 2) ? "+" : "-")
             << left << setw(6);
        int c = 0;
        for (const auto& j : polingtonSost[i]) {
            if (millerRabin(j, 2)) c++;
        }
        cout << c << endl;
    }
    cout << endl;

    //================================ТЕСТЫ НА ГОСТ
    vector<bint> gostGens;
    vector<vector<bint>> gostSost;
    for (int i = 0; i < 10; i++) {
        gostOtbros.clear();
        gostGens.push_back(gost(7, W, 1));
        gostSost.push_back(gostOtbros);
    }
    cout << "Таблица для метода по ГОСТ\n";
    cout << "№  " << setw(8) << "P" << setw(25) << "Rs" << setw(6) << "K" << endl;
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        cout << left << setw(4) << (i+1)
             << left << setw(25) << gostGens[i]
             << left << setw(6) << (millerRabin(gostGens[i], 2) ? "+" : "-")
             << left << setw(6);
        int c = 0;
        for (const auto& j : gostSost[i]) {
            if (millerRabin(j, 2)) c++;
        }
        cout << c << endl;
    }
    cout << endl;
}

//ФИНАЛЬНАЯ ПРОВЕРКА
void finaltest() {
    cout << "Желаете проверить корректность алгоритмов на данных из приложения? (1 - Да, 2 - Нет)" << endl;
    int cmd;
    cin >> cmd;
    if (cmd == 1) {
        cout << endl << "Миллер:" << endl;
        TestAlgMiller();
        cout << endl << "Полингтон:" << endl;
        TestAlgPolington();
        cout << endl << "ГОСТ:" << endl;
        TestAlgGost();
    }
}

//MAIN
int main() {
    eratosfen();
    cout << "Введите требуемую битность чисел > ";
    cin >> W;
    tables();
    finaltest();
    return 0;
}
