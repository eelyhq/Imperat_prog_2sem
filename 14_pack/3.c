#include <assert.h>
#include <stdio.h>


#if defined(__GNUC__) && !defined(__llvm__)
#define REAL_GCC   __GNUC__
#endif

int main()
{
    #if defined(REAL_GCC)
        printf("Compiler: GCC\n");

    #elif defined(__GNUC__) || defined(__clang__)
        printf("Compiler: clang\n");

    #elif defined(__TINYC__)
        printf("Compiler: TCC\n");
    #endif

    #if defined(_WIN64) ||  defined(__x86_64__)
        printf("Bitness: 64\n");
    #else
        printf("Bitness: 32\n");
    #endif


    #ifdef NDEBUG
        printf("Asserts: disabled\n");
    #else
        printf("Asserts: enabled\n");
    #endif
}