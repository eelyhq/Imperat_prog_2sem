#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 1000000000000000000LL
#define MAX_EDGES 1000001

typedef struct edge {
    int to;
    long long weight;
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


void sift_up(edge* heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].weight < heap[parent].weight) {
            edge tmp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = tmp;
            i = parent;
        } else {
            break;
        }
    }
}


void sift_down(edge* heap, int num_el) {
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < num_el && heap[left].weight < heap[smallest].weight)
            smallest = left;
        if (right < num_el && heap[right].weight < heap[smallest].weight)
            smallest = right;

        if (smallest != i) {
            edge tmp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = tmp;
            i = smallest;
        } else {
            break;
        }
    }
}


void add(edge* heap, edge val, int* num_elements)
{
    heap[*num_elements] = val;
    *num_elements += 1;
    sift_up(heap, *num_elements - 1);
}

edge extract_min(edge* heap, int* num_elements)
{
    edge res = heap[0];

    heap[0] = heap[*num_elements - 1];

    *num_elements -= 1;

    sift_down(heap, *num_elements);
    return res;
}


int main() {
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/input.txt", "r");
    FILE* f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/output.txt", "w");

    int n, m, k;

    fscanf(f_in, "%d %d %d", &n, &m, &k);

    int** requests = (int**)malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        int from, to;
        fscanf(f_in, "%d %d", &from, &to);
        requests[i] = (int*)malloc(2 * sizeof(int));
        requests[i][0] = from;
        requests[i][1] = to;
    }


    vector** adj_list = (vector**)malloc((n+1) * sizeof(vector*));
    edge* p = (edge*)malloc((n+1) * sizeof(edge));
    int num_p = 0;

    for (int i = 1; i <= n; i++)
    {
        adj_list[i] = (vector*)malloc(1 *  sizeof(vector));
        INIT(adj_list[i]);
    }

    int id = 1;
    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        fscanf(f_in, "%d %d %d", &from, &to, &weight);

        edge e = {to, weight, id};
        id++;
        PUSH(adj_list[from], e);
    }

    long long* dist = (long long*)malloc((n+1) *  sizeof(long long));


    edge* heap = (edge*)malloc(MAX_EDGES * sizeof(edge));
    int* path = (int*)malloc((n + 1) * sizeof(int));


    for (int i = 0; i < k; i++) {
        for (int q = 1; q <= n; q++)
        {
            dist[q] = INF;
            p[q].to = -1;
        }
        int num_el = 0;
        int u = requests[i][0];
        int v = requests[i][1];

        dist[u] = 0;

        add(heap, (edge){u,dist[u] }, &num_el);

        while (num_el > 0) {
            edge e = extract_min(heap, &num_el);

            if (e.weight > dist[e.to])
                continue;

            if (e.to == v)
            {
                p[0] = e;
                break;

            }

            for (int j = 0; j < adj_list[e.to] -> n; j++) {
                edge neighbour = adj_list[e.to] -> arr[j];

                if (e.weight + neighbour.weight < dist[neighbour.to]) {
                    dist[neighbour.to] = e.weight + neighbour.weight;
                    p[neighbour.to ] = e;
                    add(heap, (edge){neighbour.to, dist[neighbour.to], neighbour.id}, &num_el);
                }
            }
        }

        if (dist[v] != INF)
        {
            int path_len = 0;
            edge curr;
            curr = p[0];

            while (curr.to != -1)
            {
                path[path_len++] = curr.id;
                curr = p[curr.to];
            }
            fprintf(f_out, "quarantine %lld %d ", dist[v], path_len-1);

            for (int j = path_len - 2; j >= 0; j--)
            {
                fprintf(f_out, "%d ", path[j]);
            }
            fprintf(f_out, "\n");
        }
        else
        {
            fprintf(f_out,"DOOMED\n");
        }
        num_p = 0;
    }

    for (int i = 0; i < k; i++)
    {
        free(requests[i]);
    }
    free(requests);

    for (int i = 1; i <= n; i++)
    {
        DESTROY(adj_list[i]);
        free(adj_list[i]);
    }

    free(adj_list);
    free(heap);
    free(p);
    free(path);
    free(dist);

    return 0;
}