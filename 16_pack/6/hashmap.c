#include "hashmap.h"
#include <inttypes.h>
#include <stdlib.h>

__attribute__((visibility("default")))
HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap new_hash_map; // create structure
    new_hash_map.map = (node**)calloc(size, sizeof(node*)); // allocate memory for all elements

    new_hash_map.eq_func = ef; // add to structure funcs for hash map
    new_hash_map.hash_func = hf;

    new_hash_map.size = size;

    return new_hash_map;
}

//frees memory of hash map [self]
//note: called exactly once for every hash map created by HM_Init
__attribute__((visibility("default")))
void HM_Destroy(HashMap* self)
{
    for (int i = 0; i < self -> size; i++)
    {
        node* curr_node = self -> map[i];

        if (curr_node != NULL)
        {
            while (curr_node -> next_node != NULL)
            {
                node* next_node = curr_node -> next_node;
                free(curr_node);
                curr_node = next_node;
            }
            free(curr_node);
        }
    }
    if (self -> map != NULL)
    {
        free(self -> map);
    }
    return;
}

//returns value corresponding to the specified key [key] in hash map [self]
//if [key] is not present in the map, then returns NULL
__attribute__((visibility("default")))
cpvoid HM_Get(const HashMap* self, cpvoid key)
{
    if (self -> size == 0)
    {
        return NULL;
    }

    uint32_t hash = self -> hash_func(key)  % (self -> size);

    if (self -> map[hash] != NULL)
    {
        node* curr_node = self -> map[hash];

        while (curr_node -> next_node != NULL)
        {
            if (self -> eq_func(key, curr_node -> key))
            {
                return  curr_node -> value;
            }
            curr_node  = curr_node -> next_node;
        }
        if (self -> eq_func(key, curr_node -> key))
        {
            return  curr_node -> value;
        }
    }
    return NULL;
}

//sets value [value] for the key [key] in hash map [self]
//if [self] already has some value for [key], it is overwritten
__attribute__((visibility("default")))
void HM_Set(HashMap* self, cpvoid key, cpvoid value)
{
    if (self -> size == 0)
    {
        return;
    }

    uint32_t hash = (self -> hash_func(key)) % (self -> size);

    if (self -> map[hash] == NULL)
    {
        self -> map[hash] = (node*)malloc(sizeof(node) * 1);
        self -> map[hash] -> value = value;
        self -> map[hash] -> key = key;
        self -> map[hash] -> next_node = NULL;
    }
    else
    {
        node* curr_node = self -> map[hash];
        while (curr_node -> next_node != NULL)
        {
            if (self -> eq_func(key, curr_node -> key))
            {
                curr_node -> value = value;
                return;
            }
            curr_node = curr_node -> next_node;
        }

        if (self -> eq_func(key, curr_node -> key))
        {
            curr_node -> value = value;
            return;
        }

        curr_node -> next_node = (node*)malloc(sizeof(node) * 1);
        curr_node -> next_node -> key = key;
        curr_node -> next_node -> value = value;
        curr_node -> next_node -> next_node = NULL;
    }
    return;
}