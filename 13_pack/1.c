#include <stdio.h>
#include <string.h>

long long operate(char* op, long long a, long long b)
{
    long long res;
    if (strcmp(op, "add") == 0)
    {
        res = a + b;
    }
    else if (strcmp(op, "sub") == 0)
    {
        res = a - b;
    }
    else
    {
        res = a * b;
    }
    return res;
}

int char_to_ll(char* a)
{
    long long res = 0;
    int m = 1;
    int i = 0;
    if (a[0] == '-'){
        m = -1;
        i = 1;
    }
    for (; a[i] != '\0'; i++)
    {
        res *= 10;
        res += a[i] - '0';
    }
    res *= m;
    return res;
}

int main(unsigned int argc, char* argv[]) {
    if (argc == 1)
    {
        fprintf(stderr, "No parameters specified.");
        return 13;
    }
    if (argc == 6)
    {
        long long res;
        if (strcmp(argv[1],"-m") == 0)
        {
            res = operate(argv[3], char_to_ll(argv[4]), char_to_ll(argv[5]));
            res %= char_to_ll(argv[2]);
            if (res < 0)
            {
                res += char_to_ll(argv[2]);
            }
            printf("%lld", res);
            return 0;
        }
        if (strcmp(argv[4],"-m") == 0)
        {
            res = operate(argv[1], char_to_ll(argv[2]), char_to_ll(argv[3]));
            res %= char_to_ll(argv[5]);
            if (res < 0)
            {
                res += char_to_ll(argv[5]);
            }
            printf("%lld", res);
            return 0;
        }
    }
    else
    {
        long long res;
        res = operate(argv[1], char_to_ll(argv[2]), char_to_ll(argv[3]));
        printf("%lld", res);
        return 0;
    }
    return 0;
}