#define MAX 31360

extern int primes[MAX];
extern int num_of_primes;

typedef struct Factors {
    int k; //сколько различных простых в разложении
    int primes[32]; //различные простые в порядке возрастания
    int powers[32]; //в какие степени надо эти простые возводить
} Factors;


void Factorize (int x , Factors* res ) {
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