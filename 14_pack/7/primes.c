#include "primes.h"
#include <string.h>
#define MAX 10000020

static int primes[MAX];
static int is_precalc = 0;
static int num_of_primes = 0;
static char is_prime[MAX + 1];

int bin_search(int* arr, int x, int n)
{
    int L = 0;
    int R = n;
    int res = -1;

    while (L < R )
    {
        int M = (L+R)/2;

        if (arr[M] <= x)
        {
            res = M;
            L = M + 1;
        }
        else if (arr[M] > x)
        {
            R = M;
        }
    }
    return res;
}

static void precalc()
{
    memset(is_prime, 1, MAX);
    is_prime[0] = 0;
    is_prime[1] = 0;

    for (int i = 2; i * i < MAX; i++) {
        if (is_prime[i]  == 1) {
            for (int j = i * i; j < MAX; j+=i) {
                is_prime[j] = 0;
            }
        }
    }
    for (int i = 2; i < MAX; i++)
    {
        if (is_prime[i] == 1)
        {
            primes[num_of_primes++] = i;
        }
    }
    is_precalc = 1;
}

int isPrime ( int x )
{
    if (is_precalc == 0)
    {
        precalc();
    }

    return is_prime[x];
}

int findNextPrime ( int x )
{
    if (is_precalc == 0)
    {
        precalc();
    }
    if (isPrime(x))
    {
        return primes[bin_search(primes, x, num_of_primes) ];
    }
    return primes[bin_search(primes, x, num_of_primes) + 1 ];
}

int getPrimesCount (int l , int r )
{
    if (is_precalc == 0)
    {
        precalc();
    }
    int L;
    int R;
    if (isPrime(l))
    {
        L = bin_search(primes, l, num_of_primes);
    }
    else
    {
        L = bin_search(primes, l, num_of_primes) + 1;
    }
    if (isPrime(r))
    {
        R = bin_search(primes, r, num_of_primes) - 1;
    }
    else
    {
        R = bin_search(primes, r, num_of_primes);
    }

    return R - L + 1;

}