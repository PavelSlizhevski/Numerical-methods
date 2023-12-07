#include <cmath>
#include <iostream>

using namespace std;

double function(double x)
{
    return 1 / (1 + sqrt(x));
}

double trapezoidal(double a, double b, int step)
{
    double h = (b - a) / step;
    double s = function(a) + function(b);

    for (int i = 1; i < step; i++) {
        s += 2 * function(a + i * h);
    }

    return (h / 2) * s;
}

double simpson(double a, double b, int step)
{
    double h = (b - a) / (2 * step);
    double s = function(a) + function(b);
    for (int i = 1; i < 2 * step; i++)
    {
        s += (i % 2 == 0 ? 2 : 4) * function(a + i * h);
    }

    return (h / 3) * s;
}

int main()
{
    double a = 0;
    double b = 4.0;
    double epsilon = 1e-6;  // Точность
    int step = 1;  // Начальное количество шагов

    double Ih = trapezoidal(a, b, step);
    double Ih2 = trapezoidal(a, b, 2 * step);

    while (abs(Ih2 - Ih) > 3 * epsilon)
    {
        step *= 2;
        Ih = Ih2;
        Ih2 = trapezoidal(a, b, 2 * step);
    }

    cout << "Trapezoid method: " << Ih2 << ", number of steps: " << 2 * step << endl;

    step = 1;
    Ih = simpson(a, b, step);
    Ih2 = simpson(a, b, 2 * step);

    while (abs(Ih2 - Ih) > 3 * epsilon)
    {
        step *= 2;
        Ih = Ih2;
        Ih2 = simpson(a, b, 2 * step);
    }

    cout << "Simpson's method: " << Ih2 << ", number of steps: " << 2 * step << endl;

    return 0;
}
