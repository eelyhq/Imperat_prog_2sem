#include "integerset.h"
#include <stdlib.h>
#include <stdio.h>

#define NAME IntArray
#define TYPE int

#include "array_decl.h"
#include "array_def.h"

int comparator(const void* a, const void* b)
{
    int A = *(int*)a;
    int B = *(int*)b;
    if (A > B) return 1;
    if (A < B) return -1;
    return 0; // по возрастанию
}

int bin_search(int* arr, int value, int n)
{
    int l = 0;
    int r = n - 1;

    while (l <= r)
    {
        int m = l + (r - l) / 2;

        if (arr[m] == value)
        {
            return m;
        }
        else if (arr[m] < value)
        {
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }
    return -1;
}

typedef struct IntegerSet_s
{
    IntArray arr;
}IntegerSet;

IntegerSet* CreateSet(const int* arr, int n)
{
    IntegerSet* set = (IntegerSet*)malloc(sizeof(IntArray)); // создали указатель на тип, выделили память
    IntArray_init(&(set -> arr));// проинициализировали (занулили)

    for (int i = 0; i < n; i++)
    {
        IntArray_push(&(set -> arr), arr[i]); // добавили все элементы
    }

    qsort(set -> arr.arr, set -> arr.n, sizeof(int), comparator); // отсортировали массив целиком(это выгоднее, чем создавать новый и сортировать его)


    for (int i = 1; i < n; i++)
    {
        if (set -> arr.arr[i] == set -> arr.arr[i-1]) // проверка на дубликаты, если они есть, вернуть null
        {
            DeleteSet(set);
            return NULL;
        }
    }

    return set;
}

void DeleteSet(IntegerSet* set)
{
    if (set != NULL) // предотвращение двойного удаления
    {
        IntArray_destroy(&(set -> arr)); // удалили внутренности set(указатель на структуру вектора)
        free(set); // удалили саму структуру
    }
    return;
}

int IsInSet(IntegerSet* set, int value)
{
    if (set == NULL)
    {
        return 0;
    }
    if (bin_search(set -> arr.arr, value, set -> arr.n) == -1) // сортируем и смотрим на результат
    {
        return 0;
    }
    else
    {
        return 1;
    }
}