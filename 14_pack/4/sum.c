#include <stdlib.h>
#include <stdint.h>
#define MAX 100002

extern long long sums[MAX];
extern int N;

void Init(const int* arr , int n)
{
    sums[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        sums[i] = sums[i-1] + arr[i-1];
    }
}

int64_t Sum(int r, int l)
{
    return sums[r] - sums[l];
}