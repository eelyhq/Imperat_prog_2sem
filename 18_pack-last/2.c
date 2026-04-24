#include <stdio.h>
#define MIN(x,y) (x < y ? x : y)

int main()
{
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out = fopen("output.txt", "w");

    int n;
    fscanf(f_in, "%d", &n);

    long long answer[n+1][n+1];

    for (int s = n; s >= 0; s--)
    {
        for (int l = 0; l <= n; l++)
        {
            if (s == n)
            {
                answer[s][l] = 1;
            }
            else if (l == 0)
            {
                answer[s][l] = 0;
            }
            else
            {
                long long w = answer[s][l-1];

                if (s + l <= n)
                {
                    w += answer[s+l][l] % 1000000007;
                }
                answer[s][l] = w;
            }
        }
    }
    fprintf(f_out, "%lld", answer[0][n] % 1000000007);

    return 0;
}