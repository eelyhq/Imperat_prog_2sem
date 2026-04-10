#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FRIENDS 51
#define MAX_VERTICES 5001
#define MAX_EDGES 50001

typedef struct edge
{
    int from;
    int to;
    int weight;
}edge;

typedef struct vector{
    edge* arr ;
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

int PUSH( vector* vec , edge value ) {
    if (vec->capacity == 0) {
        vec->arr = malloc(16 * sizeof(edge));
        vec->capacity = 16;
    }

    else if (vec->n == vec->capacity) {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr,vec->capacity * sizeof(edge));
    }
    vec->arr[vec->n++] = value;
    return vec->n - 1;
}


int main()
{
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out = fopen("output.txt", "w");

    int n, m, k; // n - vertices, m - edges, k - requests(friends)

    fscanf(f_in, "%d %d %d", &n, &m, &k);

    int friends[MAX_FRIENDS];

    for (int i = 0; i < k; i++)
    {
        fscanf(f_in,"%d", &friends[i]);
    }

    vector* edge_list = (vector*)malloc((n+1) * sizeof(vector));
    int* pi = (int*)malloc((n+1) * sizeof(int));

    INIT(edge_list);

    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        fscanf(f_in, "%d %d %d", &from, &to, &weight);
        edge e = {from, to, weight};
        PUSH(edge_list, e);
    }

    int dist[MAX_VERTICES];
    memset(dist, 9000001, (n+1) * sizeof(int) );

    dist[1] = 0;

    for (int j = 0; j < n - 1; j++)
    {
        for (int i = 0; i < m; i++)
        {
            edge e = edge_list -> arr[i];
            if (dist[e.to] > dist[e.from] + e.weight)
            {
                dist[e.to] = dist[e.from] + e.weight;
                pi[e.to] = e.from;
            }
        }
    }


    int path[MAX_EDGES];
    int num_in_path = 0;

    for (int i = 0; i < k; i++)
    {
        fprintf(f_out, "%d ", dist[friends[i]]);

        int v = pi[friends[i]]; // to

        path[num_in_path++] = friends[i];
        path[num_in_path++] = v;

        while (v != 1)
        {
            v = pi[v];
            path[num_in_path++] = v;
        }
        fprintf(f_out, "%d ", num_in_path);
        for (int j = num_in_path - 1; j>=0; j--)
        {
            fprintf(f_out, "%d ", path[j]);
        }

        num_in_path = 0;

        fprintf(f_out, "\n");
    }

    DESTROY(edge_list);
    free(edge_list);
    free(pi);

    return 0;
}
