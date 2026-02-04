#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a,b;
        scanf("%d %d", &a, &b);

        while (1) {
            if (a < b) {
                int c = a;
                a = b;
                b = c;
            }

            int r = a % b;

            if (r == 0) {
                printf("%d\n", b);
                break;
            }
            else {
                a = b;
                b = r;
            }
        }
    }
    return 0;
}