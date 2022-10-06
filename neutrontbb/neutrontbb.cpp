// neutrontbb.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include<ctime>
#include<cmath>
#include<omp.h>
#include<functional>
#include<tbb/tbb.h>
#include<tbb/task_scheduler_init.h>
using namespace tbb;
using namespace std;

void Func(double sigma_c, double sigma_s, double h, int& s1, int& s2, int& s3)
{

    double sigma = sigma_c + sigma_s;
    double mu, lambda, x, x0;
    double gamma1;
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
        else if (gamma1 = (rand() % 1000 + 1) / (1000 * 1.0) < (sigma_c / sigma))
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
class Neutrontbb
{
private:
    long int N;
public:
    double sum1, sum2, sum3;
    Neutrontbb(long int n)
    {
        this->N = n;
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
    }
    Neutrontbb(Neutrontbb& intbb, split)
    {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        N = intbb.N;
    }
    void operator()(const blocked_range<long>& r) 
    {
        int s1, s2, s3;
        int sum_1=0;
        int sum_2=0;
        int sum_3=0 ;
        for (int i = r.begin();i != r.end();i++)
        {
            Func(758,4, 0.001, s1, s2, s3);
            sum_1 += s1;
            sum_2 += s2;
            sum_3 += s3;
        }
        sum1+= sum_1;
        sum2 += sum_2;
        sum3+= sum_3;
    }
    void join(Neutrontbb& intbb)
    {
        sum1 += intbb.sum1;
        sum2 += intbb.sum2;
        sum3 += intbb.sum3;
    }
};

int main()
{
    srand(time(NULL));
    long int N = 1e9;
    Neutrontbb ne(N);
    tick_count t1_start = tick_count::now();
    parallel_reduce(blocked_range<long>(0, N), ne);
    tick_count t1_stop = tick_count::now();
    cout<<ne.sum1/N <<" "<<ne.sum2/N<<" "<<ne.sum3/N<<endl<<(t1_stop - t1_start).seconds() << endl;
    double sum1=0, sum2=0, sum3=0;
    
    tick_count t2_start = tick_count::now();
    parallel_for(
        blocked_range<long>(0, N),
        [&](const blocked_range<long>& r)
        {
            int s1, s2, s3;
            for (int i = r.begin();i != r.end();i++)
            {
                Func(758,4, 0.001, s1, s2, s3);
                sum1 +=s1;
                sum2 +=s2;
                sum3 +=s3;
            }
        }
    );
    tick_count t2_stop = tick_count::now();
    cout << sum1/N  << " " << sum2/N  << " " << sum3/N << endl << (t2_stop - t2_start).seconds() << endl;;
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно 
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
