#include <iostream> 
#include <cmath> 
#include <algorithm> 

using namespace std;

void PrintMatrix(double** A, double* y, int n) // вывод системы уравнение на консоль  
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
}

double* StraightGauss(double** A, double* y, int n) // метод Гаусса 
{
    double* x, max = 0; // максимальный элемент в стобце 
    int k = 0, index = 0; // индекмс максимального элемента 
    x = new double[n];
    while (k < n)
    {
        max = abs(A[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) // нахождение максимального элемента 
        {
            if (abs(A[i][k]) > max)
            {
                max = abs(A[i][k]);
                index = i;
            }
        }
        for (int j = 0; j < n; j++) // максимальный элемент на главную диагональ 
        {
            double temp = A[k][j];
            A[k][j] = A[index][j];
            A[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;

        for (int i = k; i < n; i++) // к ступенчатому виду 
        {
            double temp = A[i][k];
            for (int j = 0; j < n; j++)
                A[i][j] = A[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k) continue;
            for (int j = 0; j < n; j++)
                A[i][j] -= A[k][j];
            y[i] -= y[k];
        }
        k++;
    }
    return y;
}

double* InverseGauss(double** A, double* y, int n, double* x) //обратный ход для нахождения переменных  
{
    for (int k = n - 1; k >= 0; k--) 
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] -= A[i][k] * x[k];
    }
    return x;
}

double* Vector_neviazki(double** A, double* y, double* InverseX, int n) {
    double* F = new double[n]; // Создаем вектор невязки
    for (int i = 0; i < n; i++) {
        F[i] = -y[i]; // Вектор невязки = отрицание вектора y
        for (int j = 0; j < n; j++) {
            F[i] += A[i][j] * InverseX[j]; // Добавляем A[i][j] * InverseX[j] к F[i]
        }
    }
    return F;
}

int main()
{
    int n = 3;
    double** A = new double* [n];
    double* y = new double[n];
    double** A2 = new double* [n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            cout << "A[" << i << "][" << j << "]= ";
            cin >> A[i][j];
        }
    }
    cout << "\n-*-*-*-*-*-*-*-\n\n";
    for (int i = 0; i < n; i++)
    {
        A2[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            A2[i][j] = A[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << "y[" << i << "]= ";
        cin >> y[i];
    }
    
    cout << "\n-*-*-*-*-*-*-*-\n\n";
    PrintMatrix(A, y, n);

    cout << "\n-*-*-*-*-*-*-*-\n\n";
    double* x = StraightGauss(A, y, n);
    double* InverseX = InverseGauss(A, y, n, x);
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "]=" << InverseX[i] << endl;
    }

    double* F = Vector_neviazki(A, y, InverseX, n);
    std::cout << "Vector neviazki = ";
    for (int i = 0; i < n; i++) {
        std::cout << F[i] << " ";
    }

    delete[] y;
    delete[] x;
    delete[] InverseX;
    delete[] F;
    for (int i = 0; i < n; i++) {
        delete[] A[i];
    }
    delete[] A;
    return 0;
}