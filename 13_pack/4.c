#include <stdio.h>
#include <stdlib.h>

int traingle[2001][2001];

int main()
{
    FILE* f_in =  fopen("input.txt", "r");
    FILE* f_out =  fopen("output.txt", "w");

    int m, t;

    fscanf(f_in,"%d %d", &m, &t);

    for (int i = 0; i < 2001; i++ )
    {
        traingle[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            traingle[i][j] = (traingle[i-1][j] + traingle[i-1][j-1]) % m;
        }
    }

    for (int i = 0; i < t;  i++)
    {
        int n,k;

        fscanf(f_in, "%d %d", &n, &k);
        if (k > n || k < 0)
        {
            fprintf(f_out,"0\n");
        }
        else
        {
            fprintf(f_out ,"%d\n", traingle[n][k]);
        }
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}
