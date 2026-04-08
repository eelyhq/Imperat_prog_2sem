#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main()
{
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/input.txt", "r");
    FILE* f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/output.txt", "w");

    int n, m, p, k; // n - num vertices, m - num edges, p - min time and shortest path, k - min time

    fscanf(f_in, "%d %d %d %d", &n, &m, &p, &k);

    int** adj_matrix = (int**)malloc(sizeof(int*) * (n+1));
    int** sons_matrix = (int**)malloc(sizeof(int*) * (n+1));

    for (int i = 1; i <= n; i++)
    {
        adj_matrix[i] = (int*)malloc((n+1) *  sizeof(int));
        sons_matrix[i] = (int*)malloc((n+1) * sizeof(int));
        for (int j = 1; j <=n; j++) {
            adj_matrix[i][j] = 9000001;
        }
        memset(sons_matrix[i], -1, (n+1) * sizeof(int));

        adj_matrix[i][i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b, time;
        fscanf(f_in, "%d %d %d", &a, &b, &time);

        if (time < adj_matrix[a][b]) {
            adj_matrix[a][b] = time;
            adj_matrix[b][a] = time;
            sons_matrix[a][b] = b;
            sons_matrix[b][a] = a;
        }
    }


    // floyd-warshall
    for (int q = 1; q <= n; q++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (adj_matrix[i][q] + adj_matrix[q][j] < adj_matrix[i][j])
                {
                    adj_matrix[i][j] =  adj_matrix[i][q]  + adj_matrix[q][j];
                    sons_matrix[i][j] = sons_matrix[i][q];
                }
            }
        }
    }

    int path[300];
    int num_in_path = 0;

    for (int i = 0; i < p; i++)
    {
        int from, to;
        fscanf(f_in, "%d %d", &from, &to);

        if (from == to) {
            fprintf(f_out, "0 1 1 1\n");
            continue;
        }

        fprintf(f_out, "%d ", adj_matrix[from][to]);

        path[num_in_path++] = from;
        int v = sons_matrix[from][to];

        while (v != to) {
            path[num_in_path++] = v;
            v = sons_matrix[v][to];
        }
        path[num_in_path++] = to;

        fprintf(f_out ,"%d ", num_in_path);

        for (int w = 0; w < num_in_path;w++) {
            fprintf(f_out,"%d ", path[w]);
        }
        fprintf(f_out, "\n");
        num_in_path = 0;
    }

    for (int i = 0; i < k; i++) {
        int from, to;
        fscanf(f_in, "%d %d", &from, &to);

        fprintf(f_out, "%d\n", adj_matrix[from][to]);
    }

    for (int i = 1; i <= n; i++) {
        free(adj_matrix[i]);
        free(sons_matrix[i]);
    }

    free(adj_matrix);
    free(sons_matrix);

    fclose(f_in);
    fclose(f_out);

    return 0;

}