#include <stdio.h>
#include <string.h>
#include <limits.h>
# define MIN(a,b) (a<b?a:b)

int main()
{
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/18_pack-last/input.txt","r");
    FILE* f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/18_pack-last/output.txt","w");

    int n, k, s, t;// n - ver, k - edges

    fscanf(f_in, "%d %d %d %d", &n, &k, &s, &t);

    int c[n+1][n+1]; // adj matrix, where el - bandwidth
    memset(c, 0, sizeof(int) * (n+1) * (n+1));
    int f[n+1][n+1]; // adj matrix, where el - current flow
    memset(f, 0, sizeof(int) * (n+1) * (n+1));

    for (int i = 0; i < k; i++)
    {
        int v, u, a;

        fscanf(f_in, "%d %d %d", &v, &u, &a);

        c[v][u] += a;
        c[u][v] += a;
    }

    int pi[n+1];
    memset(pi, 0, sizeof(int) * (n+1));
    int visited[n+1];

    int queue[n+1];
    memset(queue, 0, sizeof(int) * (n+1));
    int max_flow = 0;

    while (1)
    {
        int l = 0;
        int num_el = 0;
        memset(visited, 0, sizeof(int) * (n+1));
        visited[s] = 1;
        queue[num_el++] = s;
        while ((num_el - l )!= 0) // search path, if it don't exist - we already find max flow, else we find shortest path
        {
            int u = queue[l];
            l++;

            for (int i = 1; i <= n; i++)
            {
                if (c[u][i] - f[u][i] > 0)
                {
                    if (!visited[i])
                    {
                        visited[i] = 1;
                        queue[num_el++] = i;
                        pi[i] = u;
                    }
                }

            }
        }

        if (!visited[t])
        {
            break;
        }

        // restore path
        int bottleneck = INT_MAX;

        int x = t;

        while (x != s)
        {
            int y = pi[x];
            bottleneck = MIN(bottleneck, c[y][x] - f[y][x]);
            x = y;
        }

        max_flow += bottleneck;

        //try to make flow bigger
        x = t;
        while (x != s)
        {
            int y = pi[x];
            f[y][x] = f[y][x] + bottleneck;
            f[x][y] = f[x][y] - bottleneck;
            x = y;
        }
    }


    //find min cut
    int residual[n+1][n+1];
    // memset(residual, 0, sizeof(int) * (n+1) * (n+1));

    for (int i = 1; i<=n; i++)
    {
        for (int j = 1; j<=n;j++)
        {
            residual[i][j] = c[i][j] - f[i][j];
        }
    }

    memset(visited, 0, sizeof(int) * (n+1));
    memset(queue, 0, sizeof(int) * (n+1));

    int l = 0;
    int num_l = 0;

    queue[num_l++] = s;
    visited[s] = 1;
    // dfs
    while (num_l - l > 0)
    {
        int u = queue[l++];
        for (int v = 1; v<=n; v++)
        {
            if (!visited[v] && residual[u][v] > 0)
            {
                visited[v] = 1;
                queue[num_l++] = v;
            }
        }
    }

    int min_cut_edges[k+1][2];
    int q = 0;

    for (int u = 1; u <= n; u++)
    {
        if (visited[u])
        {
            for (int v = 1; v <= n; v++)
            {
                if (!visited[v])
                {
                    if (c[u][v] > 0)
                    {
                        min_cut_edges[q][0] = u;
                        min_cut_edges[q++][1] = v;
                    }
                }
            }
        }
    }

    fprintf(f_out, "%d %d\n", max_flow, q);

    for (int i = 0; i<q; i++)
    {
        fprintf(f_out, "%d %d\n", min_cut_edges[i][0], min_cut_edges[i][1]);
    }

    return 0;
}