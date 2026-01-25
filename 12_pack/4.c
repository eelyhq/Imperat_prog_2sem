#include  <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

uint32_t jenkins_hash(const uint8_t* key, size_t len) {
    uint32_t hash = 0;
    for (size_t i = 0; i < len; i++) {
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

typedef struct first_table{
    char name[34];
    int birth;
    char country[14];
}first;

typedef struct second_table{
    char name[34];
    char movie[24];
}second;

typedef struct Node {
    first* value;
    struct Node* next;
}Node;


void insert(Node** table, first* val, int len) {
    int hash = jenkins_hash((uint8_t*)(val -> name), strlen(val -> name) ) % len;

    if (table[hash] == NULL) {
        Node* new_node = malloc(sizeof(Node));
        new_node -> next = NULL;
        new_node -> value = val;
        table[hash] = new_node;
    }
    else {
        Node* curr_node = table[hash];
        while (curr_node -> next != NULL) {
            curr_node = curr_node -> next;
        }
        Node* new_node = malloc(sizeof(Node));
        new_node -> next = NULL;
        new_node -> value = val;
        curr_node -> next = new_node;
    }
}

void find(Node** table, second* val, int len) {
    int hash = jenkins_hash((uint8_t*)(val -> name), strlen(val -> name) ) % len;

    Node* curr_node = table[hash];

    while (curr_node != NULL) {


        if (strcmp(curr_node -> value -> name, val -> name) == 0) {
            printf("%s %d %s %s %s\n", curr_node -> value -> name, curr_node -> value -> birth,  curr_node -> value -> country,  val -> name, val -> movie);
        }
        curr_node = curr_node -> next;
    }
}

void delete_table(Node** table, int len) {
    for (int i  = 0; i  < len; i++) {
        Node* curr_node = table[i];
        while (curr_node != NULL) {
            Node* next_node = curr_node ->  next;
            free(curr_node);
            curr_node = next_node;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    first* first_table = malloc(sizeof(first) * n);

    int p = n * 1.5;
    Node** hash_table = calloc(sizeof(Node*), p);

    for (int i = 0; i < n; i++) {
        char temp_name[31];
        char temp_country[11];

        fscanf(stdin, " \"%30[^\"]\" %d \"%10[^\"]\"",  temp_name, &first_table[i].birth, temp_country);
        sprintf(first_table[i].name, "\"%s\"", temp_name);
        sprintf(first_table[i].country, "\"%s\"", temp_country);
        insert(hash_table, &first_table[i], p);
    }


    int m;
    scanf("%d", &m);

    second* second_table = malloc(sizeof(second) * m);
    for (int i = 0; i < m; i++) {
        char temp_name[31];
        char temp_movie[21];
        fscanf(stdin, " \"%30[^\"]\" \"%20[^\"]\"",  temp_name, temp_movie);
        sprintf(second_table[i].name, "\"%s\"", temp_name);
        sprintf(second_table[i].movie, "\"%s\"", temp_movie);
        find(hash_table, &second_table[i], p);
    }

    delete_table(hash_table, p);
    free(hash_table);
    free(first_table);
    free(second_table);
    return 0;
}