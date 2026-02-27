#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX 100002

int N;
long long sums[MAX];
void Init ( const int * arr , int n );
int64_t Sum ( int l , int r );
int Query ( int l , int64_t sum );



int main()
{
    FILE* f_in = fopen("input.txt","r");
    FILE* f_out = fopen("output.txt","w");

    int M;
    fscanf(f_in,"%d %d", &N, &M);

    int* array = malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++)
    {
        fscanf(f_in,"%d", &array[i]);
    }

    Init(array, N);

    for (int i = 0; i < M; i++)
    {
        int l;
        long long s;
        fscanf(f_in,"%d %lld", &l, &s);

        fprintf(f_out,"%d\n", Query(l, s));
    }
    free(array);
    fclose(f_in);
    fclose(f_out);
    return 0;
}