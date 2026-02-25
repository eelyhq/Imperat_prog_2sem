#include "modular.h"

int MOD;

int pnorm(int a)
{
    return ((a % MOD) + MOD) % MOD;
}

int padd(int a, int b)
{
    return (((a + b) % MOD) + MOD) % MOD;
}

int psub(int a, int b)
{
    return (((a - b) % MOD) + MOD) % MOD;
}

int pmul(int a, int b)
{
    return (int)(((a * 1LL * b) % MOD) + MOD) % MOD;
}

long long binpow(long long a, long long exp, long long m) {
    long long res = 1;
    a %= m;

    while (exp > 0) {
        if (exp % 2 == 1) {
            res =  (res * a) % m;
        }

        a = (a * a) % m;
        exp /= 2;
    }
    return res;
}

int pdiv(int a, int b)
{
    if (b == 0)
    {
        return 0;
    }
    return (int)(((a * 1LL *binpow(b, MOD-2,MOD)) % MOD) + MOD) % MOD;
}

