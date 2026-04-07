#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector{
    int* arr ;
    int n ;
    int capacity;
} vector;

void INIT(vector* vec) {
    vec->arr = NULL;
    vec->n = 0;
    vec->capacity = 0;
}

void DESTROY( vector* vec ) {
    if (vec->arr != NULL) {
        vec->n = 0;
        vec->capacity = 0;
        free(vec->arr);
        vec->arr = NULL;
    }
}

int PUSH( vector* vec , int value ) {
    if (vec->capacity == 0) {
        vec->arr = malloc(16 * sizeof(int));
        vec->capacity = 16;
    }

    else if (vec->n == vec->capacity) {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr,vec->capacity * sizeof(int));
    }
    vec->arr[vec->n++] = value;
    return vec->n - 1;
}

int POP( vector* vec ) {
    if (vec->n != 0) {
        return vec->arr[--vec->n];
    }
    int tmp;
    return tmp;
}

void RESERVE( vector* vec , int capacity ) {
    if (vec->capacity == 0) {
        vec->arr = malloc(16 * sizeof(int));
        vec->capacity = 16;
    }
    if (vec->capacity >= capacity) {
        return;
    }
    while (vec->capacity < capacity) {
        vec->capacity *= 2;
    }
    vec->arr = realloc(vec->arr,vec->capacity * sizeof(int));
}

void RESIZE( vector* vec , int newCnt , int fill ) {
    if (newCnt == vec->n) {
        return;
    }
    if (newCnt > vec->n) {
        RESERVE(vec, newCnt);
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
        vec -> n = newCnt;
        return;
    }
    else if (newCnt < vec->n) {
        vec->n = newCnt;
    }
}

void INSERT( vector* vec , int where , int* arr , int num ) {
    if (num == 0) {
        return;
    }
    RESERVE(vec, vec->n+num);
    for (int i = vec->n + num - 1; i >= where + num;i--) {
        vec->arr[i] = vec->arr[i-num];
    }
    for (int i = 0;i < num; i++) {
        vec->arr[where + i] = arr[i];
    }
    vec->n+= num;
}

void ERASE( vector* vec , int where, int num) {
    if (where >= vec->n || where < 0 || num <= 0) {
        return;
    }

    for (int i = where + num; i < vec->n; i++) {
        vec->arr[i-num] = vec->arr[i];
    }
    vec->n -=num;
}

int main()
{
    FILE* f_in = fopen("input.txt", "r"); // open files
    FILE* f_out = fopen("output.txt", "w");

    int n, m; // n - is num of vertice and m - is num of oriented edges
    fscanf(f_in, "%d %d", &n, &m);

    vector** adjacency_vector = (vector**)malloc((n+1) * sizeof(vector*));

    for (int i = 0; i <= n; i++)
    {
        adjacency_vector[i] = (vector*)malloc(sizeof(vector));
        INIT(adjacency_vector[i]);
    }

    for (int i = 0; i < m; i++)
    {
        int from, to;
        fscanf(f_in, "%d %d", &from, &to);

        PUSH(adjacency_vector[from], to);
    }

    int* dist = malloc((n+1) *  sizeof(int)); // index - number of vertice, value - dist from 1 to index vertice
    memset(dist, -1, (n+1) * sizeof(int));
    dist[1] = 0; // dist from 1 ver to 1 ver = 0

    int* queue = malloc(n * sizeof(int));
    int num_el_queue = 0;

    queue[num_el_queue++] = 1;
    int i = 0;

    while (i < num_el_queue)
    {
        int u = queue[i];

        for (int j = 0; j < adjacency_vector[u] -> n; j++)
        {
            int v = adjacency_vector[u] -> arr[j];

            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                queue[num_el_queue++] = v;
            }

        }
        i++;
    }

    for (int i = 1; i <= n; i++)
    {
        fprintf(f_out, "%d\n", dist[i]);
    }

    for (int i = 0; i <= n; i++)
    {
        DESTROY(adjacency_vector[i]);
        free(adjacency_vector[i]);
    }

    free(adjacency_vector);
    free(dist);
    free(queue);
    fclose(f_in);
    fclose(f_out);

    return 0;
}

