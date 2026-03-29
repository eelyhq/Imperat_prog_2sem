#include <stdio.h>
#include <math.h>

double derivative(double* C0, double* C1, double* C2, double* C3, double l, double t)
{//считаем производные
    double vx = C1[0] + 2 * C2[0] * (t - l) + 3 * C3[0] * (t - l) * (t - l);
    double vy = C1[1] + 2 * C2[1] * (t - l) + 3 * C3[1] * (t - l) * (t - l);
    double vz = C1[2] + 2 * C2[2] * (t - l) + 3 * C3[2] * (t - l) * (t - l);

    return sqrt(vx*vx + vy*vy + vz*vz);
}

double integrate(double* C0, double* C1, double* C2, double* C3, double l, double r)
{
    double h = (r-l)/1000; //маленький шаг

    double sum_ends = derivative(C0, C1, C2, C3, l, l) + derivative(C0, C1, C2, C3, l, r);

    double sum_odd = 0;

    double sum_even = 0;

    for (int i = 1; i < 1000; i++)
    {
        double с = derivative(C0, C1, C2, C3, l, l + i * h);

        if (i % 2 == 0)
        {
            sum_even += 2 * с;
        }
        else
        {
            sum_odd += 4 * с;
        }
    }
    double res = (h / 3) * (sum_ends + sum_even + sum_odd);

    return res;
}


int main()
{
    double len = 0;
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        double l, r;
        scanf("%lf %lf", &l, &r);

        double C0[4];
        double C1[4];
        double C2[4];
        double C3[4];

        for (int j = 0; j < 3; j++)
        {
            scanf("%lf %lf %lf %lf", &C0[j], &C1[j], &C2[j], &C3[j]);
        }
        len += integrate(C0, C1, C2, C3, l, r);
    }

    printf("%.16lf", len);

    return 0;
}