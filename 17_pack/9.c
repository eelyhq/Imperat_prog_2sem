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

int T = 0;
void dfs(vector** adj_list, int v, int* visited, int* t_out) {
    visited[v] = 1;

    for (int i = 0; i < adj_list[v] -> n; i++) {
        if (visited[adj_list[v] -> arr[i]] == 0) {
            dfs(adj_list, adj_list[v] -> arr[i], visited, t_out );
        }
    }
    t_out[v] = T;

    T += 1;
}


int main() {
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/input.txt", "r");
    FILE* f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/output.txt", "w");

    int n, m; // n - ver, n - edges

    fscanf(f_in, "%d %d", &m, &n);

    vector** adj_list = (vector**)malloc(sizeof(vector*)  * (n+1));

    for (int i = 1; i <= n; i++) {
        adj_list[i] = (vector*)malloc(sizeof(int) * 1);
        INIT(adj_list[i]);
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        fscanf(f_in, "%d %d", &from, &to);
        if (from == to) {
            continue;
        }
        PUSH(adj_list[from], to);
    }

   int* visited = (int*)calloc(n+1,sizeof(int));

    int* t_out = (int*)malloc((n+1) * sizeof(int));


    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            dfs(adj_list, i, visited, t_out);
        }
    }
}