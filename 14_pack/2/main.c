#include "modular.h" //в этом хедере должны быть объявления
#include <assert.h>
#include <stdio.h>


int main () {
    MOD = 13; //устанавливаем глобальный модуль
    int a = 45;
    a = pnorm(a);
    // printf("значение а %d\n", a);
    assert( a == 6);
    int x = pmul(padd (7 ,psub (2 , 3)) , 5);
    assert( x == 4);
    int y = pdiv(7 , x );
    // printf("значение x %d\n", x);
    // printf("значение y %d\n", y);
    assert(pmul(x, y) == 7);
    MOD = 2; //меняем модуль на другой
    assert (pnorm(5) == 1);

    MOD = 37;
    assert (pmul(30, 20) == 8);
    assert (psub(20, 30) == 27);

    assert(pmul(5,5) < MOD);
    MOD = 13;

    assert(pnorm(-5) == 8);

    assert(padd(5, 0) == 5);
    assert(pmul(5, 0) == 0);
    assert(pmul(5, 1) == 5);

    assert(pnorm(13) == 0);
    assert(pnorm(26) == 0);
    assert(padd(7, 6) == 0);

    assert(psub(5, 5) == 0);
    assert(psub(0, 1) == 12);
    MOD = 1000000007;
    assert(pmul(999999999, 999999999) == 64);

    assert(pdiv(64, 999999999) ==  999999999);

    return 0;
}
