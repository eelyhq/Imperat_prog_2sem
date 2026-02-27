#include <stdint.h>
#include <stdint.h>
#define MAX 100002

extern long long sums[MAX];
extern int N;
int64_t Sum ( int l , int r );


int bin_search(long long* arr, int l, int n, long long s)
{
    int L = l;
    int R = n;
    int res = -1;

    while (L <= R )
    {
        int M = (L+R)/2;

        if (Sum(M, l) <= s)
        {
            res = M;
            L = M + 1;
        }
        else if (Sum(M, l)  > s )
        {
            R = M - 1;
        }
    }
    return res;
}

int Query(int l, int64_t sum)
{
    return bin_search(sums, l, N, sum);
}
