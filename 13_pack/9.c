#include <math.h>
#include <stdio.h>
#include <stdlib.h>



int max(int** a, int n, int c, int curr)
{
    int k = -1;
    for (int i = curr; i < n; i++)
    {
        if (a[i][c] == 1)
        {
            k = i;
            break;
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

int main()
{
    int k;
    scanf("%d", &k);
    getc(stdin);

    int kk = k * k;

    int** matrix = calloc(sizeof(int*),  kk);

    for (int i = 0; i < kk; i++)
    {
        matrix[i] = calloc(sizeof(int), (kk + 1) );
    }


    int cur_equation = 0;
    for (int row = 0; row < k; row++)
    {
        for (int col = 0; col < k ; col++)
        {
            char c;
            scanf(" %c", &c);

            if (c == '.')
            {
                matrix[cur_equation][kk] = 0;
            }
            else
            {
                matrix[cur_equation][kk] = 1;
            }

            matrix[cur_equation][row * k + col] = 1;

            if ((row + 1) < k) matrix[cur_equation][(row + 1) * k + col] = 1;
            if ((row - 1) >= 0) matrix[cur_equation][(row - 1) * k + col] = 1;
            if ((col + 1) < k) matrix[cur_equation][row * k + (col + 1)] = 1;
            if ((col - 1) >= 0) matrix[cur_equation][row * k + (col - 1)] = 1;
            cur_equation++;
        }
    }

    int p = 2;
    int n = kk;

    int* where = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) where[i] = -1;

    int curr = 0;
    for (int i = 0; i < n; i++ )
    {
        if (curr == kk)
        {
            break;
        }

        int q = max(matrix, kk, i, curr);
        if (q == -1)
        {
            continue;
        }

        if (q != curr)
        {
            int* prev = matrix[curr];
            matrix[curr] = matrix[q];
            matrix[q] = prev;
        }
        where[i] = curr;
        // print(matrix, n, k );
        for (int j = curr + 1 ; j < kk; j++)
        {
            if (matrix[j][i] == 0)
            {
                continue;
            }


            for (int m = i; m <= n; m++)
            {
                matrix[j][m] ^= matrix[curr][m];
            }
            // print(matrix, n, k );
        }

        curr++;
    }




    int* answers = calloc(sizeof(int), n);

    for (int i = n - 1; i >= 0; i--)
    {
        int row = where[i];

        if (row == -1)
        {
            answers[i] = 0;
            continue;
        }

        int s = matrix[row][n];

        for (int j = i + 1; j < n; j ++)
        {
            if (matrix[row][j])
            {
                s ^= answers[j];
            }
        }

        answers[i] = s;
    }
    int w = 0;
    for (int i = 0; i < kk; i ++)
    {
        if (answers[i] == 1)
        {
            w++;
        }
    }
    printf("%d\n", w);

    for (int i = 0; i < n; i++) {
        if (answers[i] == 1)
        {
            int r = i / k + 1;
            int c = i % k + 1;
            printf("%d %d\n", r, c);
        }

    }
    free(answers);


    for (int i = 0; i < kk; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;

}