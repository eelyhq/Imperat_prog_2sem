#include <assert.h>
#include "primes.h"

int main()
{
   assert(isPrime(0) == 0);
   assert(isPrime(1) == 0);
   assert(isPrime(2) == 1);
   assert(isPrime(13) == 1);

   assert(findNextPrime(1) == 2);
   assert(findNextPrime(13) == 13);
   assert(findNextPrime(14) == 17);
   assert(findNextPrime(15) == 17);
   assert(findNextPrime(10000000) == 10000019);
   assert(findNextPrime(9999991) == 9999991);


   assert(getPrimesCount(14, 15) == 0);
   assert(getPrimesCount(0, 1) == 0);
   assert(getPrimesCount(2, 10) == 4);
   assert(getPrimesCount(13, 17) == 1);
   assert(getPrimesCount(16, 16) == 0);
   assert(getPrimesCount(7, 17) == 3);
   assert(getPrimesCount(6, 17) == 3);
   assert(getPrimesCount(8, 17) == 2);
   assert(getPrimesCount(0, 0) == 0);
   assert(getPrimesCount(8, 8) == 0);
   assert(getPrimesCount(7, 7) == 0);
   assert(getPrimesCount(0, 10000000) == 664579);






    return 0;
}