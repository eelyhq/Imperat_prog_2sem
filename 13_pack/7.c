#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


int max(double** a, int n, int c, int curr)
{
    int k = 0;//номер строки, в которой наиб эл
    double m = LLONG_MIN;
    for (int i = curr; i < n; i++)
    {
        if (fabs(a[i][c]) > m)
        {
            m = fabs(a[i][c]);
            k = i;
        }
    }
    return k;
}

void print(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    if (n == 0)
    {
        return 0;
    }

    double** matrix = malloc(sizeof(double*) * n);

    for (int i = 0; i < n; i++)
    {
        double* a = malloc(sizeof(double) * (n+1));
        matrix[i] = a;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            double c;
            scanf("%lf", &c);
            matrix[i][j] = c;
        }
    }

    // print(matrix, n);
    int curr = 0;
    for (int i = 0; i < n; i++ )
    {
        int k = max(matrix, n, i, curr);
        curr++;
        if (k != i)
        {
            double* prev = matrix[i];
            matrix[i] = matrix[k];
            matrix[k] = prev;
        }

        // print(matrix, n);
        for (int j = curr; j < n; j++)
        {
            double f = matrix[j][i] / matrix[i][i];

            for (int k = i; k <= n; k++)
            {
                matrix[j][k] = matrix[j][k] -  matrix[i][k] * f;
            }

        }
    }


    double* answers = malloc(sizeof(double) * n);
    answers[n-1] = matrix[n-1][n] /  matrix[n-1][n-1];


    for (int i = n-2 ; i >= 0; i--)
    {
        double res = matrix[i][n];
        for (int j = n - 1; j > i; j-- )
        {
            res -= matrix[i][j] * answers[j];
        }
        answers[i] = res / matrix[i][i];
    }

    for (int i = 0; i < n; i++)
    {
        printf("%lf\n", answers[i]);
    }

    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
    free(answers);

    return 0;
}