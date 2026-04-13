#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a,b) (a < b ? a : b)

int comparator(const void* a,const  void* b)
{
    int A = *(int*)a;
    int B = *(int*)b;
    return A - B;
}

typedef struct edge
{
    int to;
    int id;
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
        vec->arr = malloc(16 * sizeof(vector));
        vec->capacity = 16;
    }

    else if (vec->n == vec->capacity) {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr,vec->capacity * sizeof(vector));
    }
    vec->arr[vec->n++] = value;
    return vec->n - 1;
}


void dfs(vector** adj_list, int v, int* visited, int* level, int* up, int depth, int p_edge_id, int* bridges, int* num_bridges) {
    visited[v] = 1;
    level[v] = depth;
    up[v] = depth; // default it is his level;

    for (int i = 0; i < adj_list[v] -> n; i++) {
        int u = adj_list[v] -> arr[i].to;
        int id = adj_list[v] -> arr[i].id;

        if (id == p_edge_id)
            continue;

        if (visited[u]) // this is back edge
        {
            up[v] = MIN(up[v], level[u]); // u - back edge and then u can go back from  this edge to upper ver - update up
        }
        else
        {
            dfs(adj_list, u, visited, level, up, depth + 1, id, bridges, num_bridges);

            up[v] = MIN(up[v], up[u]); // if from sons can go to upper

            if (up[u] >= level[u]) // if current level less or equal it means that u can come in curr ver only from tree edge
            {
                bridges[*num_bridges] = id;
                *num_bridges += 1;
            }
        }
    }
}

int main()
{
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/input.txt", "r");
    FILE* f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/output.txt", "w");

    int n, m; // n - ver, m - edges

    fscanf(f_in, "%d %d", &n, &m);

    vector** adj_list = (vector**)malloc(sizeof(vector*)  * (n+1));

    for (int i = 1; i <= n; i++) {
        adj_list[i] = (vector*)malloc(sizeof(vector) * 1);
        INIT(adj_list[i]);
    }

    int id = 1;
    for (int i = 0; i < m; i++) {
        int from, to;
        fscanf(f_in, "%d %d", &from, &to);
        if (from == to) {
            id++;
            continue;
        }
        PUSH(adj_list[from], (edge){to, id}); // graph non-oriented
        PUSH(adj_list[to], (edge){from, id});
        id++;
    }

    int* level = (int*)calloc(n+1, sizeof(int));
    int* visited = (int*)calloc(n+1, sizeof(int));
    int* up = (int*)calloc(n+1, sizeof(int));
    int* bridges = (int*)malloc(sizeof(int) * (m+1));
    int num_bridges = 0;
    int depth = 0;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(adj_list, i, visited, level, up, depth, 0, bridges, &num_bridges);
        }
    }

    fprintf(f_out, "%d\n", num_bridges );
    qsort(bridges, num_bridges, sizeof(int), comparator);
    for (int i = 0; i < num_bridges; i++)
    {
        fprintf(f_out, "%d ", bridges[i]);
    }

    for (int i = 1; i <= n; i++) {
        DESTROY(adj_list[i]);
        free(adj_list[i]);
    }

    free(adj_list);
    free(level);
    free(visited);
    free(up);
    free(bridges);

    fclose(f_in);
    fclose(f_out);

    return 0;
}