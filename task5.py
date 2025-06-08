def simulate_cooling(T0, Ts, r, dt, total_time):
    T = T0
    steps = int(total_time / dt)
    print("\n+--------------+-------------------------+")
    print("| Время (с)    | Температура кофе (°C)   |")
    print("+--------------+-------------------------+")
    for i in range(steps + 1):
        time = i * dt
        print(f"| {time:12.2f} | {T:23.2f} |")
        T += -r * (T - Ts) * dt
    print("+--------------+-------------------------+")

def main():
    T0 = float(input("Введите начальную температуру кофе (T0): "))
    Ts = float(input("Введите температуру окружающей среды (Ts): "))
    r = float(input("Введите коэффициент остывания (r): "))
    dt = float(input("Введите шаг по времени (dt): "))
    total_time = float(input("Введите общее время моделирования (в секундах): "))
    simulate_cooling(T0, Ts, r, dt, total_time)

if __name__ == "__main__":
    main()
