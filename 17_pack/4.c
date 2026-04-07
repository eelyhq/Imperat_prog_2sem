#include <stdio.h>
#include <stdlib.h>

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


int dfs(vector** adj_list, int v, int* visited, int* t_out, int* mark, int* num_out_ver)
{
    mark[v] = 1;
    visited[v] = 1;

    for (int i = 0; i < adj_list[v] -> n; i++ )
    {
        if (mark[adj_list[v] -> arr[i]] == 0)
        {
            int f = dfs(adj_list, adj_list[v] -> arr[i], visited, t_out, mark, num_out_ver);
            if (f != -1)
            {
                return v;
            }
        }
        else if (mark[adj_list[v] -> arr[i]] == 1)
        {
            return v; // we come to gray vertice -> there is a cycle
        }
    }
    mark[v] = 2;
    t_out[v] = (*num_out_ver)--;
    return -1;
}

void clear(vector** adj_list, int n, int* visited, int* t_out, int* mark)
{
    for (int i = 0; i < n; i++)
    {
        free(adj_list[i]);
    }
    free(adj_list);
    free(visited);
    free(t_out);
    free(mark);
    return;
}
// main idea - make oriented graph with edges (X1,X2),
// where X1<X2 on condition. then make check O(n) on cycles
// by dfs and O(N) for give values to vertices by val of exit from dfs

int main()
{
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out  = fopen("output.txt", "w");

    int n, m; // n - vertices, m - edges

    fscanf(f_in, "%d %d", &n, &m);

    vector** adjacency_list = (vector**)malloc(sizeof(vector*) * (n+1));

    for (int i = 1; i <= n; i++)
    {
        adjacency_list[i] = (vector*)calloc(1, sizeof(vector));
    }

    for (int i = 0; i < m; i++)
    {

        int from, to;

        fscanf(f_in,"%d %d", &from, &to);

        PUSH(adjacency_list[from], to);
    }

    int* visited = (int*)calloc((n+1), sizeof(int));
    int* t_out = (int*)calloc((n+1), sizeof(int)); // time of out from vertice in dfs
    int* mark = (int*)calloc((n+1), sizeof(int)); // 0 - white, 1 - gray, 2 - black

    int num_out_ver = n;

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            int f = dfs(adjacency_list, i,visited, t_out, mark, &num_out_ver);
            if (f != -1)
            {
                fprintf(f_out, "NO");
                clear(adjacency_list, n, visited, t_out, mark);
                return 0;
            }
        }
    }

    fprintf(f_out, "YES\n");

    for (int i = 1; i <= n; i++)
    {
        fprintf(f_out, "%d ", t_out[i]);
    }
    return 0;

}