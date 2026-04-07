#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertice
{
    int row;
    int col;
}vertice;

int main()
{
    FILE* f_in = fopen("input.txt", "r"); // open files
    FILE* f_out = fopen("output.txt", "w");

    int m, n; // m - width, n - height
    fscanf(f_in,"%d %d", &m, &n);

    int ch;
    while ((ch = fgetc(f_in)) != '\n' && ch != EOF);

    char** labyrinth = (char**)malloc(sizeof(char*) * (m+10)); // allocate memory for labyrinth
    int** dist = (int**)malloc(sizeof(int*) * (m + 10));

    int row_start = -1;
    int col_start = -1;

    int row_finish = -1;
    int col_finish = -1;

    for (int i = 0; i < m; i++)
    {
        dist[i] = (int*)malloc(sizeof(int) * (n + 1));
        memset(dist[i], -1, (n+1) * sizeof(int));

        labyrinth[i] = (char*)malloc(sizeof(char) * (n+10));
        fgets(labyrinth[i], n+5, f_in); // read i-th string and add to array

        if (row_finish == -1 || row_start == -1)
        {
            for (int j = 0; j < n; j++ )
            {
                if (labyrinth[i][j] == 'S')
                {
                    row_start = i;
                    col_start = j;
                }
                if (labyrinth[i][j] == 'F')
                {
                    row_finish = i;
                    col_finish = j;
                }
            }
        }
    }


    dist[row_start][col_start] = 0;

    vertice* queue = malloc((n * m) * sizeof(vertice));
    int num_el_queue = 0;

    vertice start;
    start.col = col_start;
    start.row = row_start;

    queue[num_el_queue++] = start;

    int i = 0;

    while (i < num_el_queue)
    {
        vertice u = queue[i];

        if (u.row - 1 >= 0 && (labyrinth[u.row - 1][u.col] == '.' || labyrinth[u.row - 1][u.col] == 'F') && dist[u.row - 1][u.col] == -1)
        {
            dist[u.row - 1][u.col] = dist[u.row][u.col] + 1;
            vertice v;
            v.col = u.col;
            v.row = u.row - 1;
            queue[num_el_queue++] = v;
        }
        if (u.row + 1 < m && (labyrinth[u.row + 1][u.col] == '.' || labyrinth[u.row + 1][u.col] == 'F') && dist[u.row + 1][u.col] == -1)
        {
            dist[u.row + 1][u.col] = dist[u.row][u.col] + 1;
            vertice v;
            v.col = u.col;
            v.row = u.row + 1;
            queue[num_el_queue++] = v;
        }
        if (u.col - 1 >= 0 && (labyrinth[u.row][u.col - 1] == '.' || labyrinth[u.row][u.col - 1] == 'F') && dist[u.row][u.col - 1] == -1)
        {
            dist[u.row][u.col - 1] = dist[u.row][u.col] + 1;
            vertice v;
            v.col = u.col - 1;
            v.row = u.row;
            queue[num_el_queue++] = v;
        }
        if (u.col + 1 < n && (labyrinth[u.row][u.col + 1] == '.' || labyrinth[u.row][u.col + 1] == 'F') && dist[u.row][u.col + 1] == -1)
        {
            dist[u.row][u.col + 1] = dist[u.row][u.col] + 1;
            vertice v;
            v.col = u.col + 1;
            v.row = u.row;
            queue[num_el_queue++] = v;
        }
        i++;
    }

    fprintf(f_out,"%d", dist[row_finish][col_finish]);

    for (int i = 0; i < m; i++)
    {
        free(labyrinth[i]);
        free(dist[i]);
    }
    free(dist);
    free(labyrinth);
    free(queue);

    fclose(f_in);
    fclose(f_out);

    return 0;

}