
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Функция fx возвращает пару (x, y) по тому же принципу, что и на графике:
pair<float,float> fx(float x) {
    if (x < 0) {
        // левая часть: y = -0.5*x
        return {x, -0.5f * x};
    }
    else if (x <= 2) {
        // 0 <= x <= 2: (x - 0)^2 + (y - 2)^2 = 4  => y = 2 - sqrt(4 - x^2)
        float y = 2.0f - sqrtf(4.0f - x*x);
        return {x, y};
    }
    else if (x <= 4) {
        // 2 < x <= 4: (x - 2)^2 + (y - 0)^2 = 4  => y =  sqrt(4 - (x-2)^2)
        float y = sqrtf(4.0f - (x - 2.0f)*(x - 2.0f));
        return {x, y};
    }
    else {
        // x > 4: y = -0.5*(x - 4)
        float y = -0.5f * (x - 4.0f);
        return {x, y};
    }
}

int main() {
    // Лучше сразу читать x_start, x_end как float, чтобы шаг мог быть дробным
    float x_start, x_end, step;
    cout << "Через пробел введите x начальное, x конечное и шаг x: ";
    cin >> x_start >> x_end >> step;

    cout << fixed << setprecision(2);
    cout << setw(8) << "x" << setw(10) << "y" << endl;
    cout << "-------------------------" << endl;
    for (float x = x_start; x <= x_end; x += step) {
        auto p = fx(x);
        cout << setw(8) << p.first << setw(10) << p.second << endl;
    }
    return 0;
}
