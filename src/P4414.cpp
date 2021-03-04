#include <math.h>
#include <stdio.h>
#include <string.h>
int main() {
    char str[3];
    int a[3], i, j, t;
    for (i = 0; i < 3; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%s", str);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        t = str[i] - 'A';
        printf("%d ", a[t]);
    }

    return 0;
}
