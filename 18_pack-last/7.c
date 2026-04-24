#include <stdio.h>
#include <string.h>

char controller[15][15][105];

int res[15];
FILE* f_out;

void print_solution(int n)
{
    fprintf(f_out, "YES\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(f_out, "%d\n", res[i] + 1);
    }
    return;
}

int rec(int* lamps, int p, int n, int k, int m, int l)
{
    // p - current controller
    if (p == n) // all lamps has correct voltage
    {
        print_solution(n);
        return 1;
    }

    for (int i = 0; i < k; i++) // try to turn on all switchers
    {
        int f = 0;
        for (int j = 0; j < m; j++)
        {
            if (controller[p][i][j] == 'X') // it means, that j-th lamp will increase voltage
            {
                lamps[j] += 1;
            }
        }

        // cutting off 2
        if (!f)
        {
            for (int q = 0; q < m; q++) {
                if (lamps[q] + (n - 1 - p) < l || lamps[q] > l) // it means that, if we even if we pull all the remaining levers, this lamp will have lack of voltage or that voltage more than normal -> we can't push this lever
                {
                    f = 1;
                    break;
                }
            }
        }

        if (!f)
        {
            res[p] = i;
            int e = rec(lamps, p+1, n, k, m, l);
            if (e)
            {
                return 1;
            }
        }

        for (int j = 0; j < m; j++)
        {
            if (controller[p][i][j] == 'X') // it means, that j-th lamp will decrase voltage
            {
                lamps[j] -= 1;
            }
        }
    }
    return 0;
}

int main()
{
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/18_pack-last/input.txt","r");
    f_out = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/18_pack-last/output.txt","w");
    int n, k, m, l;

    fscanf(f_in, "%d %d %d %d\r\n", &n, &k, &m, &l);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int q = 0; q < m; q++)
            {
                fscanf(f_in, "%c", &controller[i][j][q]);
            }
            fscanf(f_in, "\r\n");
        }
    }

    int lamps[m];
    memset(lamps, 0, sizeof(int) * m);

    memset(res, 0, sizeof(int) * n);

    int f = rec(lamps, 0, n, k, m, l);

    if (!f)
    {
        fprintf(f_out, "NO");
    }
    return 0;
}