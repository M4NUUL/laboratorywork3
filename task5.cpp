#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Функция моделирования остывания кофе
void simulateCooling(double T0, double Ts, double r, double dt, double totalTime) {
    double T = T0;
    int steps = static_cast<int>(totalTime / dt);

    // Заголовок таблицы
    cout << "\n+--------------+-------------------------+\n";
    cout << "| Время (с)    | Температура кофе (°C)   |\n";
    cout << "+--------------+-------------------------+\n";

    cout << fixed << setprecision(2);

    for (int i = 0; i <= steps; ++i) {
        double time = i * dt;

        cout << "| " << right << setw(12) << time << " | " << right << setw(23) << T << " |\n";

        T += -r * (T - Ts) * dt;
    }

    cout << "+--------------+-------------------------+\n";
}

int main() {
    double T0, Ts, r, dt, totalTime;

    // Ввод параметров
    cout << "Введите начальную температуру кофе (T0): ";
    cin >> T0;

    cout << "Введите температуру окружающей среды (Ts): ";
    cin >> Ts;

    cout << "Введите коэффициент остывания (r): ";
    cin >> r;

    cout << "Введите шаг по времени (dt): ";
    cin >> dt;

    cout << "Введите общее время моделирования (в секундах): ";
    cin >> totalTime;

    // Запуск моделирования
    simulateCooling(T0, Ts, r, dt, totalTime);

    return 0;
}
