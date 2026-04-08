#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/input.txt", "r");
    FILE* f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/17_pack/output.txt", "r");

    int n, m, p, k; // n - num vertices, m - num edges, p - min time and shortest path, k - min time

    fscanf(f_in, "%d %d %d %d", &n, &m, &p, &k);

    int** adj_matrix = (int**)malloc(sizeof(int*) * (n+1));
    int** sons_matrix = (int**)malloc(sizeof(int*) * (n+1));

    for (int i = 1; i <= n; i++)
    {
        adj_matrix[i] = (int*)malloc((n+1) *  sizeof(int));
        memset(adj_matrix[i], -1, (n+1) * sizeof(int));
        memset(sons_matrix[i], -1, (n+1) * sizeof(int));
        adj_matrix[i][i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b, time;
        fscanf(f_in, "%d %d %d", &a, &b, &time);

        adj_matrix[a][b] = time;
        adj_matrix[b][a] = time;
        sons_matrix[a][b] = b;
        sons_matrix[b][a] = a;
    }


    // floyd-warshall
    for (int k = 1; k < n; k++)
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (adj_matrix[i][k] + adj_matrix[k][j] < adj_matrix[i][j])
                {
                    adj_matrix[i][j] =  adj_matrix[i][k]  + adj_matrix[k][j];
                    sons_matrix[i][j] = sons_matrix[i][k];
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
        fprintf(f-in, "%d ", adj_matrix[from][to]);


    }



}
