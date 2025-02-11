#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

// Функция, которую будем минимизировать
double function(double x) {
    // Пример функции: f(x) = (x-2)^2
    return pow(x - 2, 2);
}

// Метод пассивного поиска
void passive_search(double a, double b, int N, double epsilon, double& xmin, double& fmin) {
    vector<double> x(N);
    vector<double> fx(N);

    // Если количество точек четное
    if (N % 2 == 0) {
        int l = N / 2;
        for (int j = 1; j <= l; ++j) {
            x[2 * j - 2] = a + (b - a) / (N / 2 + 1) * j - epsilon / 2;
            x[2 * j - 1] = a + (b - a) / (N / 2 + 1) * j + epsilon / 2;
        }
    }
    // Если количество точек нечетное
    else {
        for (int i = 1; i <= N; ++i) {
            x[i - 1] = a + (b - a) / (N + 1) * i;
        }
    }

    // Вычисляем значения функции в точках
    for (int i = 0; i < N; ++i) {
        fx[i] = function(x[i]);
    }

    // Находим минимум функции и соответствующую точку
    auto min_iter = std::min_element(fx.begin(), fx.end());
    int k = std::distance(fx.begin(), min_iter);

    xmin = x[k];
    fmin = fx[k];

    // Итоговый отрезок локализации
    double xk_minus_1 = (k - 1 >= 0) ? x[k - 1] : a;
    double xk_plus_1 = (k + 1 < N) ? x[k + 1] : b;

    std::cout << "Отрезок локализации: [" << xk_minus_1 << ", " << xk_plus_1 << "]" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a, b;
    double epsilon = 0.01; // Малое положительное число
    int N;
    cout << "Введите левую границу отрезка a: ";
    cin >> a; //-5
    cout << "Введите правую границу отрезка b: ";
    cin >> b; //5
    cout << "Введите количество точек N: ";
    cin >> N; //3

    double xmin = 0.0;
    double fmin = std::numeric_limits<double>::max();

    passive_search(a, b, N, epsilon, xmin, fmin);

    cout << "Аппроксимация точки минимума: x* = " << xmin << endl;
    cout << "Значение функции в точке минимума: f* = " << fmin << endl;

    return 0;
}
