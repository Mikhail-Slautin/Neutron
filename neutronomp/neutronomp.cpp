// neutronomp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include<ctime>
#include<cmath>
#include<omp.h>
using namespace std;

void Func(double sigma_c, double sigma_s, double h, int& s1, int& s2, int& s3)
{
    double sigma = sigma_c + sigma_s;
    double mu, lambda, x, x0;
    double gamma1, gamma2, gamma3;
    x0 = 0;
    mu = 0;
    bool c;
    c = true;
    while (c)
    {
        gamma1 = 0;
        gamma1 = (rand() % 1000 + 1) / (1000 * 1.0);
        lambda = (-log(gamma1)) / sigma;
        x = x0 + lambda * mu;
        gamma1 = 0;

        if (x > h)
        {
            s1 = 1;
            s2 = 0;
            s3 = 0;
            c = false;
        }
        else if (x < 0)
        {
            s1 = 0;
            s2 = 1;
            s3 = 0;
            c = false;
        }
        else if (gamma1 = (rand() % 100000 + 1) / (100000 * 1.0) < (sigma_c / sigma))
        {
            s1 = 0;
            s2 = 0;
            s3 = 1;
            c = false;
        }
     
        else
        {
            gamma1 = 0;
            gamma1 = (rand() % 1000 + 1) / (1000 * 1.0);
            x0 = x;
            mu = 2 * gamma1 - 1;
        }
    }
}

int main()
{
    srand(time(NULL));
    double P1, P2, P3;
    int s1;
    int s2;
    int s3;
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    int N = 1e9;
    double start;
    double stop;
    start = omp_get_wtime();
#pragma omp parallel for reduction(+:sum1,sum2,sum3)
    for (int i = 0;i < N;i++)
    {
        Func(758,4.8, 0.001, s1, s2, s3);
        sum1 += s1;
        sum2 += s2;
        sum3 += s3;
    }
    P1 = (double)sum1 / N;
    P2 = (double)sum2 / N;
    P3 = (double)sum3 / N;
    stop = omp_get_wtime();
    cout << P1 << " " << P2 << " " << P3 << endl;
    cout << stop - start;

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
