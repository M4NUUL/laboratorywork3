import math

# Функция fx возвращает пару (x, y) по тому же принципу, что и на графике:
def fx(x):
    if x < 0:
        # левая часть: y = -0.5*x
        return x, -0.5 * x
    elif x <= 2:
        # 0 <= x <= 2: (x - 0)^2 + (y - 2)^2 = 4  => y = 2 - sqrt(4 - x^2)
        y = 2.0 - math.sqrt(4.0 - x * x)
        return x, y
    elif x <= 4:
        # 2 < x <= 4: (x - 2)^2 + (y - 0)^2 = 4  => y = sqrt(4 - (x-2)^2)
        y = math.sqrt(4.0 - (x - 2.0) * (x - 2.0))
        return x, y
    else:
        # x > 4: y = -0.5*(x - 4)
        y = -0.5 * (x - 4.0)
        return x, y

def main():
    x_start, x_end, step = map(float, input("Через пробел введите x начальное, x конечное и шаг x: ").split())
    print(f"{'x':>8}{'y':>10}")
    print('-' * 25)
    x = x_start
    while x <= x_end + 1e-8:  # чтобы не пропустить последний шаг из-за погрешности
        px, py = fx(x)
        print(f"{px:8.2f}{py:10.2f}")
        x += step

if __name__ == "__main__":
    main()
