#include  <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct first_table{
    char name[34];
    int birth;
    char country[14];
}first;

typedef struct second_table{
    char name[34];
    char movie[24];
}second;

int comparator(const void *a, const void *b) {
    const first* A = a;
    const first* B = b;

    return strcmp(A -> name ,B -> name);
}

void merge(first* f, second* s, int n, int m) {
    int u1 = 0;
    int u2 = 0;

    while ((u1 < n) && (u2 < m)) {
        if (strcmp(f[u1].name, s[u2].name) < 0) {
            u1++;
        }
        else if (strcmp(f[u1].name, s[u2].name) > 0) {
            u2++;
        }
        else {
            int st1 = u1;
            int st2 = u2;
            while (u1 < n && strcmp(f[u1].name, f[st1].name) == 0) {
                u1++;
            }
            while (u2 < m && strcmp(s[u2].name, s[st2].name) == 0) {
                u2++;
            }

            for (int i = st1; i < u1; i++) {
                    for (int j = st2; j < u2; j++) {
                        printf("%s %d %s %s %s\n", f[i].name, f[i].birth, f[i].country, s[j].name, s[j].movie);
                    }
                }
            }
        }

    }


int main() {
    int n;
    scanf("%d", &n);

    first* first_table = malloc(sizeof(first) * n);



    for (int i = 0; i < n; i++) {
        char temp_name[31];
        char temp_country[11];

        fscanf(stdin, " \"%30[^\"]\" %d \"%10[^\"]\"",  temp_name, &first_table[i].birth, temp_country);
        sprintf(first_table[i].name, "\"%s\"", temp_name);
        sprintf(first_table[i].country, "\"%s\"", temp_country);
    }

    qsort(first_table, n, sizeof(*first_table), comparator);


    int m;
    scanf("%d", &m);

    second* second_table = malloc(sizeof(second) * m);
    for (int i = 0; i < m; i++) {
        char temp_name[31];
        char temp_movie[21];
        fscanf(stdin, " \"%30[^\"]\" \"%20[^\"]\"",  temp_name, temp_movie);
        sprintf(second_table[i].name, "\"%s\"", temp_name);
        sprintf(second_table[i].movie, "\"%s\"", temp_movie);
    }

    qsort(second_table, m, sizeof(*second_table), comparator);

    merge(first_table, second_table, n,m);

    free(first_table);
    free(second_table);
    return 0;
}