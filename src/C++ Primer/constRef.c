#include <stdio.h>
#include <string.h>


int main() {
    char str[100];
    int i, len;
    gets(str);
    len = strlen(str);

    for (i = len-1; i >= 0;i--) {
        printf("%d\n", str[i]);
    }
}