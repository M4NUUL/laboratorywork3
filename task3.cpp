#include <iostream>
#include <cstring>
#include <numeric>

using namespace std;

long long gcd(long long a, long long b) {
    a = abs(a);
    b = abs(b);
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long power(long long base, int exp) {
    long long res = 1;
    while (exp > 0) {
        if (exp % 2) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}

long long A[11][11]; // Числа Эйлера

void computeEulerian(int max_n) {
    memset(A, 0, sizeof(A));
    A[0][0] = 1;
    for (int n = 1; n <= max_n; ++n) {
        for (int k = 0; k < n; ++k) {
            long long term1 = (k > 0 ? (n - k) * A[n - 1][k - 1] : 0);
            long long term2 = (k + 1) * A[n - 1][k];
            A[n][k] = term1 + term2;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    if (a < 1 || a > 10 || b < 1 || b > 10) {
        cerr << "Input values must be in [1, 10]." << endl;
        return 1;
    }

    if (b == 1) {
        cout << "infinity" << endl;
        return 0;
    }

    computeEulerian(a);

    long long num = 0;
    for (int j = 0; j < a; ++j)
        num += A[a][j] * power(b, a - j);

    long long denom = power(b - 1, a + 1);
    long long g = gcd(num, denom);

    cout << (num / g) << "/" << (denom / g) << endl;

    return 0;
}
