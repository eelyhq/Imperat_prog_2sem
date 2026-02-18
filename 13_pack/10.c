#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    int m,n;
    scanf("%d %d", &n, &m);

    double** X = malloc(sizeof(double*) * 100);
    double** Y = malloc(sizeof(double*) * 100);

    for (int i = 0; i < 100; i++)
    {
        X[i] = malloc(sizeof(double) * 12);
        Y[i] = malloc(sizeof(double) * 12);
    }

    double K = 100.0;
    double T = 12.0;

    for (int i = 0; i < 100; i++)//filling array with arguments
    {
        double start = i / K;//this is begining of subsegment
        double finish = (i + 1) / K;//end

        double len = finish - start;

        double step = len / (T - 1);

        for (int j = 0; j < 12; j++)
        {
            X[i][j] = start + j * step;
        }
    }

    double W[10000], A[10000], B[10000];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf %lf", &W[i], &A[i], &B[i]);

    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            double res = 0;
            for (int k = 0; k < n;k++)
            {
                res += W[k] * cos(A[k] * X[i][j] + B[k]);
            }
            Y[i][j] = res;
        }
    }


    for (int i = 0; i < 100; i++) {
        for (int k = 1; k < 12; k++) {
            for (int j = 11; j >= k; j--) {

                double chisl = Y[i][j] - Y[i][j-1];
                double znam = X[i][j] - X[i][j-k];

                Y[i][j] = chisl / znam;
            }
        }
    }


    for (int i = 0; i < m; i++)
    {
        double x;
        scanf("%lf", &x);

        int num_segment = (int)(x * 100);

        if (num_segment == 100)
        {
            num_segment = 99;
        }

        double res = Y[num_segment][11];
        for (int j = 10; j >= 0; j--)
        {
            res =  Y[num_segment][j] + (x - X[num_segment][j]) * res;
        }
        printf("%.15f\n", res);
    }
    for (int i = 0; i < 100; i++)
    {
        free(X[i]);
        free(Y[i]);
    }
    free(X);
    free(Y);
    

    return 0;
}