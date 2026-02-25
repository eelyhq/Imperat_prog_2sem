#include <stdint.h>
#define MAX 100002

long long sums = malloc(sizeof(long long) * MAX);

void Init(const int* arr , int n)
{
    sums[0] = 0;

    for (int i = 1; i < n; i++)
    {
        sums[i] = sums[i-1] + arr[i];
    }
}

int64_t Sum(int l, int r)
{
    return sums[]
}