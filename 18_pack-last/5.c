#include <stdio.h>
#include <string.h>
#include <limits.h>
# define MIN(a,b) (a<b?a:b)

int main()
{
    FILE* f_in = fopen("input.txt","r");
    FILE* f_out = fopen("output.txt","w");

    int a, b, m;// a - ver in left part, b - ver in right part, m - edges

    fscanf(f_in, "%d %d %d", &a, &b, &m);

    int n = a + b + 2; // num of ver: a + b + source and dist, which we will add

    int s = n - 1; // indexes of source and dest ver
    int t = n;

    int c[n+1][n+1]; // adj matrix, where el - bandwidth
    memset(c, 0, sizeof(int) * (n+1) * (n+1));
    int f[n+1][n+1]; // adj matrix, where el - current flow
    memset(f, 0, sizeof(int) * (n+1) * (n+1));

    for (int i = 0; i < m; i++)
    {
        int v, u;

        fscanf(f_in, "%d %d", &v, &u);

        c[v][u + a] = 1; // all bandwidth = 1. u+b need, to make nums of vers in left and right part - different
        // connect our artificially added drain and source
        c[s][v] = 1;
        c[u+a][t] = 1;
    }

    int pairs[a+1];
    memset(pairs, 0, sizeof(int) * (a+1));
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
            if (x != t && y != s)
            {
                pairs[y] = x-a;
            }
            x = y;

        }
    }

    fprintf(f_out, "%d\n", max_flow);

    for (int i = 1; i <= a; i++)
    {
        if (pairs[i] != 0)
        {
            fprintf(f_out, "%d %d\n", i, pairs[i]);
        }
    }
    return 0;
}