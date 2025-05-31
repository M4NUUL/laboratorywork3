#include <iostream>
#include <vector>
#include <random>
#include <set>

using namespace std;

vector<int> sieve(int max) {
    vector<bool> isPrime(max + 1, true);
    vector<int> primes;
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= max; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= max; j += i)
                isPrime[j] = false;
        }
    }
    return primes;
}

int modPow(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (1LL * result * base) % mod;
        base = (1LL * base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int randPrime(const vector<int>& primes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, primes.size() - 1);
    return primes[dist(gen)];
}

bool pocklingtonTest(int n, int F, const vector<int>& qList, int t) {
    set<int> aList;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, n - 2);

    while (aList.size() < t)
        aList.insert(dist(gen));

    for (int a : aList) {
        if (modPow(a, n - 1, n) != 1)
            return false;

        bool passed = true;
        for (int q : qList) {
            if (modPow(a, (n - 1) / q, n) == 1) {
                passed = false;
                break;
            }
        }
        if (passed)
            return true;
    }
    return false;
}

int main() {
    vector<int> primes = sieve(500);
    int k = 0;

    cout << "№\tP\tТест\tk\n";

    int attempts = 0;
    long long i = 1;
    while (attempts < 10) {
        long long R = 2 * i;
        int q = randPrime(primes);
        long long F = q;
        long long n = R * F + 1;

        if (n > 500 || n % 2 == 0) {
            ++i;
            continue;
        }

        vector<int> qList = {q};

        if (pocklingtonTest((int)n, (int)F, qList, 5)) {
            cout << (attempts + 1) << "\t" << n << "\t+\t" << k << "\n";
            k = 0;
        } else {
            cout << (attempts + 1) << "\t" << n << "\t-\t" << k << "\n";
            k++;
        }
        attempts++;
        ++i;
    }
    return 0;
}
