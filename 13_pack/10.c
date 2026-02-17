#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x, double w, double a, double b)
{
    double res = w * cos(a*x+b);

    return res;
}

int main()
{
    int m,n;
    scanf("%d %d", &n, &m);

    double** X = malloc(sizeof(double*) * 1000);
    double** Y = malloc(sizeof(double*) * 1000);

    for (int i = 0; i < 1000; i++)
    {
        X[i] = malloc(sizeof(double) * 9);
        Y[i] = malloc(sizeof(double) * 9);
    }

    double K = 1000.0;
    double T = 9.0;

    for (int i = 0; i < 1000; i++)//filling array with arguments
    {
        double start = i / K;//this is begining of subsegment
        double finish = (i + 1) / K;//end

        double len = finish - start;

        double step = len / (T - 1);

        for (int j = 0; j < 9; j++)
        {
            X[i][j] = start + j * step;
        }
    }

    double** koeffs = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++)
    {
        koeffs[i] = malloc(sizeof(double) * 3);
        double w, a, b;
        scanf("%lf %lf %lf", &w, &a, &b);
        koeffs[i][0] = w;
        koeffs[i][1] = a;
        koeffs[i][2] = b;
    }

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            double res = 0;
            for (int k = 0; k < n;k++)
            {
                res += f(X[i][j],koeffs[k][0],koeffs[k][1],koeffs[k][2]);
            }
            Y[i][j] = res;
        }
    }


    for (int i = 0; i < 1000; i++) {
        for (int k = 1; k < 9; k++) {
            for (int j = 8; j >= k; j--) {

                double chisl = Y[i][j] - Y[i][j-1];
                double znam = X[i][j] - X[i][j-k];

                Y[i][j] = chisl / znam;
            }
        }
    }


}