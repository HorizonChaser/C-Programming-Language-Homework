#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CStack
{
    char *stack;
    int cnt;
}CStack;

char* initStack(char* stack) {
    stack = (char *)malloc(10 * sizeof(char *));
}
