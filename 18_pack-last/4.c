#include <stdio.h>
#include <string.h>
#define MAX_N 5001

int main()
{
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out = fopen("output.txt", "w");

    int n;
    fscanf(f_in, "%d", &n);

    int dp[MAX_N]; // i-th el - max len of curr sequence include curr
    int pi[MAX_N];
    memset(pi, -1, sizeof(int) * MAX_N);
    int arr[MAX_N];

    int max_seq_res = 0; // this is max len of subseq
    int index_last_el = 0; // this is index of last el in max subseq
    for (int i = 0; i < n; i++)
    {
        fscanf(f_in, "%d", &arr[i]);
    }

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1; // base-case

        int max_seq = 0;
        int index_max_seq = -1;

        for (int j = i-1; j  >= 0; j--)
        {
            if (dp[j] > max_seq && arr[j] < arr[i])
            {
                index_max_seq = j;
                max_seq = dp[j];
            }
        }

        if (index_max_seq  != -1)
        {
            dp[i] += dp[index_max_seq];
            pi[i] = index_max_seq;
            if (dp[i] > max_seq_res)
            {
                max_seq_res = dp[i];
                index_last_el = i;
            }

        }
    }

    if (max_seq_res == 0)
    {
        fprintf(f_out, "1\nA[1] = %d", arr[0]);
        return 0;
    }

    fprintf(f_out, "%d\n", max_seq_res);

    int subseq[MAX_N];
    int h = max_seq_res;

    int x = index_last_el;
    subseq[--max_seq_res] = x;

    while (x != -1)
    {
        int y = pi[x];
        subseq[--max_seq_res] = y;
        x = y;
    }

    for (int i = 0; i < h; i++)
    {
        fprintf(f_out,"A[%d] = %d\n", subseq[i] + 1, arr[subseq[i]]);
    }

    return 0;
}