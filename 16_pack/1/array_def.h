#include <stdlib.h>

void INIT(NAME* vec) {
    vec->arr = NULL;
    vec->n = 0;
    vec->capacity = 0;
}

void DESTROY( NAME* vec ) {
    if (vec->arr != NULL) {
        vec->n = 0;
        vec->capacity = 0;
        free(vec->arr);
        vec->arr = NULL;
    }
}

int PUSH( NAME* vec , TYPE value ) {
    if (vec->capacity == 0) {
        vec->arr = malloc(16 * sizeof(TYPE));
        vec->capacity = 16;
    }

    else if (vec->n == vec->capacity) {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr,vec->capacity * sizeof(TYPE));
    }
    vec->arr[vec->n++] = value;
    return vec->n - 1;
}

TYPE POP( NAME* vec ) {
    if (vec->n != 0) {
        return vec->arr[--vec->n];
    }
    TYPE tmp;
    return tmp;
}

void RESERVE( NAME* vec , int capacity ) {
    if (vec->capacity == 0) {
        vec->arr = malloc(16 * sizeof(TYPE));
        vec->capacity = 16;
    }
    if (vec->capacity >= capacity) {
        return;
    }
    while (vec->capacity < capacity) {
        vec->capacity *= 2;
    }
    vec->arr = realloc(vec->arr,vec->capacity * sizeof(TYPE));
}

void RESIZE( NAME* vec , int newCnt , TYPE fill ) {
    if (newCnt == vec->n) {
        return;
    }
    if (newCnt > vec->n) {
        RESERVE(vec, newCnt);
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
        vec -> n = newCnt;
        return;
    }
    else if (newCnt < vec->n) {
        vec->n = newCnt;
    }
}

void INSERT( NAME* vec , int where , TYPE* arr , int num ) {
    if (num == 0) {
        return;
    }
    RESERVE(vec, vec->n+num);
    for (int i = vec->n + num - 1; i >= where + num;i--) {
        vec->arr[i] = vec->arr[i-num];
    }
    for (int i = 0;i < num; i++) {
        vec->arr[where + i] = arr[i];
    }
    vec->n+= num;
}

void ERASE( NAME* vec , int where, int num) {
    if (where >= vec->n || where < 0 || num <= 0) {
        return;
    }

    for (int i = where + num; i < vec->n; i++) {
        vec->arr[i-num] = vec->arr[i];
    }
    vec->n -=num;
}
