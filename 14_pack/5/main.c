#include <stdlib.h>
#include <stdio.h>

typedef struct Factors {
    int k; //сколько различных простых в разложении
    int primes[32]; //различные простые в порядке возрастания
    int powers[32]; //в какие степени надо эти простые возводить
} Factors;

void Factorize ( int x , Factors * res );

int main() {
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out = fopen("output.txt", "w");


    int M;
    fscanf(f_in,"%d", &M);

    Factors** factors = malloc(sizeof(Factors*) * M);
    for (int i = 0; i < M; i++) {
        factors[i] = malloc(sizeof(Factors) * M);
    }
    int nums[1001];
    int cur = 0;
    for (int i = 0; i < M; i++) {
        int x;
        fscanf(f_in,"%d", &x);
        nums[cur] = x;
        Factorize(x, factors[cur++]);
    }

    for (int i = 0; i < M; i++) {
        fprintf(f_out,"%d =", nums[i]);
        if (factors[i] -> k == 0)
        {
            fprintf(f_out," 1");
        }
        for (int j = 0; j < factors[i] -> k; j++) {
            fprintf(f_out ," %d^%d", factors[i] -> primes[j], factors[i] -> powers[j]);
            if (j + 1 != factors[i] -> k)
            {
                fprintf(f_out, " *");
            }
        }
        fprintf(f_out,"\n");
    }
    fclose(f_in);
    fclose(f_out);
    for (int i = 0; i < M; i++) {
        free(factors[i]);
    }
    free(factors);
    return 0;
}