#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int binpow(int a, int exp, int m) {
    int res = 1;
    a %= m;

    while (exp > 0) {
        if (exp % 2 == 1) {
            res =  (res * 1LL * a) % m;
        }

        a = (a * 1LL *  a) % m;
        exp /= 2;
    }
    return res;
}

int max(int** a, int n, int c, int curr)
{
    int k = curr;//номер строки, в которой наиб эл

    for (int i = curr; i < n; i++)
    {
        if (abs(a[i][c]) > abs(a[k][c]))
        {
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

    for (int i = 0; i < k; i++) {
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

    int rank = 0;
    int curr = 0;
    for (int i = 0; i < n; i++ )
    {
        if (curr == k)
        {
            break;
        }

        int q = max(matrix, k, i, curr);
        if (matrix[q][i] == 0)
        {
            continue;
        }

        if (q != curr)
        {
            int* prev = matrix[curr];
            matrix[curr] = matrix[q];
            matrix[q] = prev;
        }
        // print(matrix, n, k );
        for (int j = curr + 1 ; j < k; j++)
        {
            if (matrix[j][i] == 0)
            {
                continue;
            }
            int f = matrix[j][i] * 1LL * binpow(matrix[curr][i], p-2, p) % p;

            for (int m = i; m <= n; m++)
            {
                matrix[j][m] = (matrix[j][m] -  matrix[curr][m] * 1LL *  f) % p;
                matrix[j][m] = (matrix[j][m] % p + p) % p;
            }
            // print(matrix, n, k );
        }
        rank++;
        curr++;
    }

    int free_vars = n - rank;

    int f = 0;

    for (int i = 0; i < k; i++)
    {
        int zeros = 1;
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != 0)
            {
                zeros = 0;
                break;
            }
        }
        if (zeros && matrix[i][n] != 0)
        {
            f = 1;
            break;
        }

    }

    if (f)
    {
        printf("0");
    }
    else if (free_vars > 0)
    {
        printf("%d", binpow(p, n - rank, 1000000007));
    }
    else
    {
        int* answers = malloc(sizeof(int) * n);

        for (int i = n - 1; i >= 0; i--)
        {
            long long s = matrix[i][n];

            for (int j = i + 1; j < n; j ++)
            {
                s  = (s - (matrix[i][j] * 1LL * answers[j]) % p + p) % p;
            }

            answers[i] = (s * 1LL * binpow(matrix[i][i], p - 2, p)) % p;
        }
        printf("1\n");
        for (int i = 0; i < n; i++) {
            printf("%d\n", answers[i]);
        }
        free(answers);
    }

    for (int i = 0; i < k; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}