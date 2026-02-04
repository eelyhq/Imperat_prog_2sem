#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int* arr = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", arr[i]);
    }

    int lim = 2 * n - 1;

    int l = 0;
    int r = 0;
    int max = arr[0];

    for (int i = 0; i < lim; i++) {
        char c;
        scanf("%c", &c);

        if (c == 'R') {
            r++;
            if (arr[r] > max) {
                max  = arr[r];
            }
        }
        else {
            
        }
    }
}