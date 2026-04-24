#include <stdio.h>
#define MAX_COL 13
#define MAX_ROW 13
#define MAX_DIAG 25

FILE* f_out;
char field[MAX_COL][MAX_ROW];
// 0 - free, 1 - busy
int hasC[MAX_COL] = {0}; // index - num of col
int hasS[MAX_DIAG] = {0}; // c + r - index of back diagonals
int hasD[MAX_DIAG] = {0}; // r - c - index of straight diagonals. also need to + 12, because it may be negative

void print_answer(int n, int m)
{
    fprintf(f_out, "YES\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (field[i][j] == 'X')
            {
                fprintf(f_out, "X");
                continue;
            }
            fprintf(f_out, ".");
        }
        fprintf(f_out, "\n");
    }
}

int rec(int m, int n, int r)
{
    if (r == m)
    {
        print_answer(n,m);
        return 1;
    }

    for (int c = 0; c < n; c++)
    {
        if (hasC[c] || hasS[c+r] || hasD[r-c+12] || field[r][c] == '.') // . - couldn't place queen
            continue;

        field[r][c] = 'X'; // X - placed queen

        hasC[c] = 1;
        hasS[c+r] = 1;
        hasD[r-c+12] = 1;

        int f =  rec(m, n, r+1);

        field[r][c] = '?'; // ? - possible place for queen, but not suitable
        if (f)
        {
            return 1;
        }

        hasC[c] = 0;
        hasS[c+r] = 0;
        hasD[r-c+12] = 0;
    }
    return 0;
}

int main()
{
    FILE* f_in = fopen("input.txt", "r");
    f_out = fopen("output.txt", "w");

    int m, n; // m - num of rows, n - num of col -> needed to place m queens

    fscanf(f_in, "%d %d", &m, &n);

    if(n < m || (m <= 3 && n <= 3)){ // it is impossible to place queens, with m < 3 this problem don't solve
        fprintf(f_out, "NO");
        return 0;
    }

    while ((fgetc(f_in)) != '\n'); // read all trash symbols

    for (int i = 0; i < m; i++)
    {
        fgets(field[i], n + 3, f_in); // n + 3 to read also /r/n etc.
    }

    int f = rec(m, n, 0);

    if (!f)
    {
        fprintf(f_out, "NO");
    }

    return 0;
}