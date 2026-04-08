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


int dfs(vector** adj_list, int v, int* visited, int* gray_ver, int* mark, int* num_gray_ver)
{
    mark[v] = 1;
    gray_ver[(*num_gray_ver)++] = v;

    visited[v] = 1;

    for (int i = 0; i < adj_list[v] -> n; i++ )
    {
        if (mark[adj_list[v] -> arr[i]] == 0)
        {
            int f = dfs(adj_list, adj_list[v] -> arr[i], visited, gray_ver, mark, num_gray_ver);
            if (f != -1)
            {
                return f;
            }
        }
        else if (mark[adj_list[v] -> arr[i]] == 1)
        {
            return adj_list[v] -> arr[i]; // we come to gray vertice -> there is a cycle
        }
    }
    mark[v] = 2;
    (*num_gray_ver)--; // work like stack
    return -1;
}

void clear(vector** adj_list, int n, int* visited, int* gray_vertices, int* mark)
{
    for (int i = 1; i < n; i++)
    {
        DESTROY(adj_list[i]);
    }
    free(adj_list);
    free(visited);
    free(gray_vertices);
    free(mark);
    return;
}


int main() {
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out  = fopen("output.txt", "w");


    int n, m; // n - vertices, m - edges

    fscanf(f_in, "%d %d", &n, &m);

    vector** adjacency_list = (vector**)malloc(sizeof(vector*) * (n+1));

    for (int i = 1; i <= n; i++)
    {
        adjacency_list[i] = (vector*)calloc(1, sizeof(vector));
        INIT(adjacency_list[i]);
    }

    for (int i = 0; i < m; i++)
    {

        int from, to;

        fscanf(f_in,"%d %d", &from, &to);

        PUSH(adjacency_list[from], to);
    }


    int* visited = (int*)calloc((n+1), sizeof(int));
    int* gray_vertices = (int*)calloc((n+1), sizeof(int)); // time of out from vertice in dfs
    int* mark = (int*)calloc((n+1), sizeof(int)); // 0 - white, 1 - gray, 2 - black

    int num_gray_ver = 0;

    int flag = 0;
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            int f = dfs(adjacency_list, i,visited, gray_vertices, mark, &num_gray_ver);
            if (f != -1) {
                for (int j = 0; j < num_gray_ver; j++) {
                    if (gray_vertices[j] == f)
                    {
                        flag = 1;
                    }
                    if (flag)
                    {
                        int k = j;
                        fprintf(f_out,"%d\n", num_gray_ver - j);
                        for (int q = j; q < num_gray_ver; q++)
                        {
                            fprintf(f_out, "%d ", gray_vertices[q]);
                        }
                        clear(adjacency_list, n, visited, gray_vertices, mark);
                        return 0;
                    }
                }

            }
        }
    }

    fprintf(f_out,"-1");

    clear(adjacency_list, n, visited, gray_vertices, mark);

    return 0;
}