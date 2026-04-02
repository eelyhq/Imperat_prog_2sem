#include "hashmap.h"
#include <stdlib.h>

//creates and returns new hash table with:
// [ef] –- function which compares keys for equality
// [hf] –- function which produces a hash for a key
// [size] –- prescribed size/capacity of the hash table (number of cells)
HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap* new_hash = (HashMap*)malloc(sizeof(HashMap) * 1);
}

//frees memory of hash map [self]
//note: called exactly once for every hash map created by HM_Init
void HM_Destroy(HashMap * self);

//returns value corresponding to the specified key [key] in hash map [self]
//if [key] is not present in the map, then returns NULL
cpvoid HM_Get(const HashMap* self, cpvoid key);

//sets value [value] for the key [key] in hash map [self]
//if [self] already has some value for [key], it is overwritten
void HM_Set(HashMap* self, cpvoid key, cpvoid value);