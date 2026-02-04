#include <stdio.h>

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

int main() {
    long long m;
    int t;
    scanf("%d %lld", &t, &m);

    for (int i = 0; i < t; i++) {
        long long a;
        scanf("%lld", &a);


        long long b = binpow(a, m-2, m);


        if (((b * a) % m) == 1 && b >= 0 && b < m) {
            printf("%lld\n", b);
        }
        else {
            printf("-1\n");
        }

    }
    return 0;
}