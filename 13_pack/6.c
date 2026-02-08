#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000002
#define MOD 1000000007

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

int main()
{
    int t;
    scanf("%d", &t);

    int* fact = malloc(sizeof(int) * MAX_N);
    fact[0] = 1;
    fact[1] = 1;

    for (int i = 2; i < MAX_N; i++)
    {
        fact[i] = (fact[i-1] * 1LL * i)  % MOD ;
    }

    int* inv_fact = malloc(sizeof(int) * MAX_N);

    inv_fact[MAX_N-1] = binpow(fact[MAX_N-1],MOD - 2, MOD);

    for (int i = MAX_N - 2; i >= 0; i--)
    {
        inv_fact[i] = (inv_fact[i + 1] * 1LL * (i + 1)) % MOD ;
    }

    for (int i = 0; i < t; i++)
    {
        int k,n;
        scanf("%d %d", &n, &k);
        if (k < 0 || k > n)
        {
            printf("0");
        }
        else
        {
            printf("%lld\n", (((fact[n] * 1LL * inv_fact[k]) % MOD) * (inv_fact[n-k] * 1LL)) % MOD);
        }
    }
    free(fact);
    free(inv_fact);
    return 0;
}