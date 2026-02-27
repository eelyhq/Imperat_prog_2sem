#include <string.h>
#define MAX 35000

int primes[MAX];
int num_of_primes;
int is_precalc = 0;
int num_of_primes = 0;

typedef struct Factors {
    int k; //сколько различных простых в разложении
    int primes[32]; //различные простые в порядке возрастания
    int powers[32]; //в какие степени надо эти простые возводить
} Factors;


void Factorize (int x , Factors* res ) {

    if (is_precalc == 0)
    {
        char is_prime[MAX + 1];
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
    res->k = 0;
    for (int i = 0; i < num_of_primes; i++) {
        if (primes[i] * primes[i] > x) {
            break;
        }

        if (x % primes[i] == 0) {
            res -> k++;
            while (x % primes[i] == 0) {
                (res -> powers[res -> k-1])++;
                x /= primes[i];
            }
            res -> primes[res -> k-1] = primes[i];
        }
    }
    if (x > 1) {
        res -> primes[res -> k] = x;
        res -> powers[res -> k] = 1;
        res -> k++;
    }
}