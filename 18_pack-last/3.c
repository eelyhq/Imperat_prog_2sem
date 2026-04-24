#include <stdio.h>
#include <string.h>
#include <limits.h>
# define MIN(a,b) (a<b?a:b)

int main()
{
    FILE* f_in = fopen("input.txt","r");
    FILE* f_out = fopen("output.txt","w");

    int n, k;// n - ver, k - edges

    fscanf(f_in, "%d %d", &n, &k);

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
        visited[1] = 1;
        queue[num_el++] = 1;
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

        if (!visited[n])
        {
            break;
        }

        // restore path
        int bottleneck = INT_MAX;

        int x = n;

        while (x != 1)
        {
            int y = pi[x];
            bottleneck = MIN(bottleneck, c[y][x] - f[y][x]);
            x = y;
        }

        max_flow += bottleneck;

        //try to make flow bigger
        x = n;
        while (x != 1)
        {
            int y = pi[x];
            f[y][x] = f[y][x] + bottleneck;
            f[x][y] = f[x][y] - bottleneck;
            x = y;
        }
    }

    fprintf(f_out, "%d", max_flow);

    return 0;
}