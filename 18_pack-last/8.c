#include <stdio.h>
#include <string.h>
#define MAX_N 201
#define MAX_W 50001
#define MAX(a,b) (a<b?b:a)

int dp[MAX_N][MAX_W];

void find_ans(int k, int i, int* ans, int* num_in_ans, int* w, int* s)
{
    if (dp[k][i] == 0)
    {
        return;
    }
    if (dp[k-1][i] == dp[k][i])
    {
        find_ans(k-1, i, ans, num_in_ans, w, s);
    }
    else
    {
        find_ans(k - 1, i - w[k], ans, num_in_ans, w, s);
        ans[*num_in_ans] = k;
        *num_in_ans += 1;
        *s += w[k];
    }
}


int main()
{
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/18_pack-last/input.txt","r");
    FILE* f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/18_pack-last/output.txt","w");

    int n, W; // n - num of items, w - max weight

    fscanf(f_in, "%d %d", &n, &W);

    int c[MAX_N];
    int w[MAX_N];

    for (int i = 1; i <= n; i++)
    {
        fscanf(f_in, "%d %d", &w[i], &c[i]);
    }


    memset(dp, 0, sizeof(int) * (MAX_N * MAX_W));

    for (int k = 0; k <= n; k++)
    {
        for (int i = 1; i <= W; i++)
        {
            if (k == 0 || i == 0)
            {
                dp[k][i] = 0;
            }
            else if (w[k] <= i)
            {
                dp[k][i] = MAX(dp[k-1][i], dp[k-1][i - w[k]] + c[k]);
            }
            else
            {
                dp[k][i] = dp[k-1][i];
            }
        }
    }

    int ans[MAX_N];
    int num_in_ans = 0;

    int sum_weight = 0;

    find_ans(n, W, ans, &num_in_ans, w, &sum_weight);

    fprintf(f_out, "%d %d %d\n", num_in_ans, sum_weight, dp[n][W]);

    for (int i = 0; i < num_in_ans; i++)
    {
        fprintf(f_out, "%d ", ans[i]);
    }
}
