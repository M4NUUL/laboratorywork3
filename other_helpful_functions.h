//Возведение a в степень b по модулю m
int powMod(int a, int b, int m) {
    int result = 1;
    a = a % m;  //на случай, если a >= m
    while (b > 0) {
        if (b % 2 == 1)
            result = (1LL * result * a) % m;  //1LL для предотвращения переполнения
        a = (1LL * a * a) % m;
        b /= 2;
    }
    return result;
}
