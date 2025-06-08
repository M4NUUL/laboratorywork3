def fx(x):
    if x < 0:
        return x, -0.5 * x
    elif x <= 2:
        y = 2.0 - (4.0 - x * x) ** 0.5
        return x, y
    elif x <= 4:
        y = (4.0 - (x - 2.0) ** 2) ** 0.5
        return x, y
    else:
        y = -0.5 * (x - 4.0)
        return x, y

def main():
    x_start, x_end, step = map(float, input("Через пробел введите x начальное, x конечное и шаг x: ").split())
    print(f"{'x':>8}{'y':>10}")
    print("-" * 25)
    x = x_start
    while x <= x_end + 1e-8:
        x_val, y_val = fx(x)
        print(f"{x_val:8.2f}{y_val:10.2f}")
        x += step

if __name__ == "__main__":
    main()
