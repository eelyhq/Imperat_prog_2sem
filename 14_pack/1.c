#include <stdio.h>

long long gcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long x1, y1;
    long long d = gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return d;
}

long long inv(long long a, long long m)
{
    long long x, y;
    long long g = gcd(a, m, &x, &y);

    if (g != 1) {

        return -1;
    }

    return (x % m + m) % m;
}

int main()//ньютон
{
    int k;
    scanf("%d", &k);

    long long M[100];
    long long A[100];


    long long P = 1;

    for (int i = 0; i < k; i++)
    {
        scanf("%lld", &M[i]);
    }

    for (int i = 0; i < k; i++)
    {
        scanf("%lld", &A[i]);
    }


    long long x = 0;


    for (int i = 0; i < k; i++)
    {

        long long diff = A[i] - x % M[i];


        diff = (diff % M[i] + M[i]) % M[i];

        long long inV = inv(P % M[i], M[i]);

        long long c = (diff * inV) % M[i];

        x = x + c * P;

        P = P * M[i];
    }

    printf("%lld", x);

    return 0;
}

// int main() //Лагранж
// {
//     int k;
//     scanf("%d", &k);
//
//
//     long long M[100];
//     long long A[100];
//
//
//     long long P = 1;
//
//     for (int i = 0; i < k; i++)
//     {
//         scanf("%lld", &M[i]);
//         P *= M[i];
//     }
//
//     for (int i = 0; i < k; i++)
//     {
//         scanf("%lld", &A[i]);
//     }
//
//     long long x = 0;
//
//     for (int i = 0; i < k; i++)
//     {
//         long long m = P / M[i];
//         long long inV = inv(m % M[i], M[i]);
//
//         long long t = A[i] * inV % M[i];
//         t = t * m ;
//         x = (x + t) % P;
//     }
//
//     printf("%lld", x) ;
//
//     return 0;
// }
//
