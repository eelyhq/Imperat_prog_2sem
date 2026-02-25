#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    int* array = malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", array[i]);
    }

}