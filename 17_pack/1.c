#pragma comment(linker, "/STACK:50000000")

#include <stdio.h>
#include <stdlib.h>

void dfs(char** labyrinth, int row, int col, int n)
{
    labyrinth[row][col] = '#'; // switch space to hash, it means that this cell is visited

    if (row - 1 >= 0 && labyrinth[row - 1][col] == ' ') // if cell left not visited yet, and it is in correct range, then make dfs from this cell
    {
        dfs(labyrinth, row - 1, col, n);
    }
    if (row + 1 < n && labyrinth[row + 1][col] == ' ') // if cell right not visited yet, and it is in correct range, then make dfs from this cell
    {
        dfs(labyrinth, row + 1, col, n);
    }
    if (col - 1 >= 0 && labyrinth[row][col - 1] == ' ') // if cell up not visited yet, and it is in correct range, then make dfs from this cell
    {
        dfs(labyrinth, row, col - 1, n);
    }
    if (col + 1 < n && labyrinth[row][col + 1] == ' ') // if cell down not visited yet, and it is in correct range, then make dfs from this cell
    {
        dfs(labyrinth, row, col + 1, n);
    }
    return;
}

int main()
{
    FILE* f_in = fopen("input.txt", "r"); // open files
    FILE* f_out = fopen("output.txt", "w");

    int n; // size of labyrinth n*n include
    fscanf(f_in,"%d", &n);

    int ch;
    while ((ch = fgetc(f_in)) != '\n' && ch != EOF);

    char** labyrinth = (char**)malloc(sizeof(char*) * n); // allocate memory for labyrinth

    int res = 0;
    for (int i = 0; i < n; i++)
    {
        labyrinth[i] = (char*)malloc(sizeof(char) * (n+10));
        fgets(labyrinth[i], n+5, f_in); // read i-th string and add to array
    }

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (labyrinth[row][col] == ' ')
            {
                dfs(labyrinth, row, col, n);
                res++; // every time, after dfs we increment num of connected component
            }
        }
    }

    for (int i = 0; i < n; i++) // free rows
    {
        free(labyrinth[i]);
    }
    free(labyrinth);

    fprintf(f_out,"%d", res - 1);
    fclose(f_in);
    fclose(f_out);
    return 0;
}