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


void dfs(vector** adj_list, int v, int* visited, int* t_out, int* num_t_out) {
    visited[v] = 1;

    for (int i = 0; i < adj_list[v] -> n; i++) {
        if (visited[adj_list[v] -> arr[i]] == 0) {
            dfs(adj_list, adj_list[v] -> arr[i], visited, t_out, num_t_out);
        }
    }
    t_out[*num_t_out] = v;
    *num_t_out += 1;
}

void dfs2(vector** adj_list, int v, int* visited, int* csc, int* curr_csc) {
    visited[v] = 1;

    for (int i = 0; i < adj_list[v] -> n; i++) {
        if (visited[adj_list[v] -> arr[i]] == 0) {
            dfs2(adj_list, adj_list[v] -> arr[i], visited, csc, curr_csc);
        }
    }

    csc[v] = *curr_csc;
}


int main() {
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out = fopen("output.txt", "w");

    int n, m; // n - ver, m - edges

    fscanf(f_in, "%d %d", &n, &m);

    vector** adj_list = (vector**)malloc(sizeof(vector*)  * (n+1));
    vector** adj_list_transpon = (vector**)malloc(sizeof(vector*)  * (n+1));

    for (int i = 1; i <= n; i++) {
        adj_list[i] = (vector*)malloc(sizeof(vector) * 1);
        adj_list_transpon[i] = (vector*)malloc(sizeof(vector) * 1);
        INIT(adj_list[i]);
        INIT(adj_list_transpon[i]);
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        fscanf(f_in, "%d %d", &from, &to);
        if (from == to) {
            continue;
        }
        PUSH(adj_list[from], to);
        PUSH(adj_list_transpon[to], from);
    }

    int* visited = (int*)calloc(n+1,sizeof(int));
    int* t_out = (int*)malloc((n+1) * sizeof(int));

    int num_t_out = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            dfs(adj_list, i, visited, t_out, &num_t_out);
        }
    }

    int* csc = (int*)malloc((n+1) * sizeof(int));
    memset(visited, 0, (n+1) * sizeof(int));

    int curr_csc = 1;
    for (int i = num_t_out - 1; i >= 0 ; i--) // go for verices in order from max to min t_out
    {
        if (visited[t_out[i]] == 0)
        {
            dfs2(adj_list_transpon, t_out[i], visited, csc, &curr_csc);
            curr_csc++;
        }
    }

    fprintf(f_out, "%d\n", curr_csc-1);

    for (int i = 1; i <= n; i++ )
    {
        fprintf(f_out, "%d ", csc[i]);
    }

    for (int i = 1; i <= n; i++) {
        DESTROY(adj_list[i]);
        DESTROY(adj_list_transpon[i]);
        free(adj_list_transpon[i]);
        free(adj_list[i]);
    }

    free(adj_list_transpon);
    free(adj_list);
    free(visited);
    free(t_out);
    free(csc);

    fclose(f_in);
    fclose(f_out);

    return 0;
}