#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


int max(int** a, int n, int c, int curr)
{
    int k = 0;//номер строки, в которой наиб эл
    int m = INT_MIN;
    for (int i = curr; i < n; i++)
    {
        if (abs(a[i][c]) > m)
        {
            m = abs(a[i][c]);
            k = i;
        }
    }
    return k;
}


void print(int** matrix, int n, int k)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n,k,p;
    scanf("%d %d %d",&n,&k,&p);


    int** matrix = malloc(sizeof(int*) * k);

    for (int i = 0; i < p; i++) {
        matrix[i] = malloc(sizeof(int) * (n+1));
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            int c;
            scanf("%d", &c);
            matrix[i][j] = c;
        }
    }

    int curr = 0;
    for (int i = 0; i < k; i++ )
    {
        int q = max(matrix, k, i, curr);
        curr++;
        if (q != i)
        {
            int* prev = matrix[i];
            matrix[i] = matrix[q];
            matrix[q] = prev;
        }

        // print(matrix, n);
        for (int j = curr; j < k; j++)
        {
            double f = matrix[j][i] / matrix[i][i];

            for (int m = i; m <= n; m++)
            {
                matrix[j][m] = matrix[j][m] -  matrix[i][m] * f;
            }

        }
    }


    print(matrix, n, k );
}