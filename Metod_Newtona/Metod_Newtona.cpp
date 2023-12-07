#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> func(const vector<double>& x, double pi) // Функция для вычисления значения функции
{
    vector<double> f(2);
    f[0] = pow(x[0], 2) - x[1] + 1;
    f[1] = x[0] - cos((pi / 2) * x[1]);
    return f;
}
 
vector<vector<double>> jacobian_analytical(const vector<double>& x, double pi) // Функция для вычисления аналитической матрицы Якоби
{
    vector<vector<double>> J(2, vector<double>(2));
    J[0][0] = 2 * x[0];
    J[0][1] = -1;
    J[1][0] = 1;
    J[1][1] = pi * sin((pi / 2) * x[1]);
    return J;
}

vector<vector<double>> jacobian_numerical(const vector<double>& x, double pi) // Функция для вычисления численной матрицы Якоби
{
    double eps2 = 1e-9;
    vector<vector<double>> J(2, vector<double>(2));
    for (int i = 0; i < 2; ++i) {
        vector<double> x_plus_h = x;
        x_plus_h[i] += eps2;
        vector<double> x_minus_h = x;
        x_minus_h[i] -= eps2;
        vector<double> f_plus_h = func(x_plus_h, pi);  
        vector<double> f_minus_h = func(x_minus_h, pi);  
        for (int j = 0; j < 2; ++j) {
            J[j][i] = (f_plus_h[j] - f_minus_h[j]) / (2 * eps2);
        }
    }
    return J;
}

vector<double> Gauss_method(vector<vector<double>> a, vector<double> b)
{
    int n = b.size();
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(a[j][i]) > abs(a[pivot][i])) {
                pivot = j;
            }
        }
        swap(a[i], a[pivot]);
        swap(b[i], b[pivot]);
        for (int j = i + 1; j < n; ++j) {
            double factor = a[j][i] / a[i][i];
            for (int k = i; k < n; ++k) {
                a[j][k] -= factor * a[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            b[i] -= a[i][j] * x[j];
        }
        x[i] = b[i] / a[i][i];
    }
    return x;
}

vector<double> Newton_method(vector<double> x0, bool analytical_jacobian, double pi) 
{
    double eps1 = 1e-9;
    vector<double> x = x0;
    for (int iter = 0; iter < 50; ++iter) {
        vector<double> f = func(x, pi);
        vector<vector<double>> J;
        if (analytical_jacobian) {
            J = jacobian_analytical(x, pi);
        }
        else {
            J = jacobian_numerical(x, pi);  
        }
        vector<double> dx = Gauss_method(J, f);
        for (int i = 0; i < 2; ++i) {
            x[i] -= dx[i];
        }
        if (sqrt(x[0] * x[0] + x[1] * x[1]) < eps1) {
            break;
        }
    }
    return x;
}

int main() 
{
    vector<double> x0 = { 1, 0 };
    const double PI = acos(-1.0); 

    vector<double> x_analytical = Newton_method(x0, true, PI);
    vector<double> x_numerical = Newton_method(x0, false, PI);
    cout << "Solution with analytic Jacobi matrix: " << x_analytical[0] << ", " << x_analytical[1] << std::endl;
    cout << "Solution with numerical Jacobi matrix: " << x_numerical[0] << ", " << x_numerical[1] << std::endl;
    return 0;
}