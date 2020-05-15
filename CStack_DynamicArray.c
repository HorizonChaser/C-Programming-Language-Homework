#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CStack
{
    int pos;
    int size;
    int dataNum;
    char* data;
}CStack;

int initStack(CStack* stack) {
    stack->data = (char *)malloc(10 * sizeof(char *));
    if(stack == NULL) {
        printf("Bad Mem Allocate\nExiting Now...\n");
        return -1;
    }
    stack->pos = 0;
    stack->size = 10;
    stack->dataNum = 0;
    return 0;
}

CStack* enlargeStack(CStack* stack) {
    stack->size*=2;
    char *newStack = (char *)malloc(10 * stack->size * sizeof(char *));
    if(newStack == NULL) {
        return NULL;
    }
    memset(newStack, NULL, 10 * stack->size * sizeof(char *));
    memcpy(newStack, stack, 10 * stack->size/2 * sizeof(char *));
    stack->data = newStack;
    return stack;
}

int printAll(CStack* stack) {
    if(stack == NULL || stack->pos == 0)
        return -1;
    for (int i = 0; i < stack->pos;i++) {
        //char *a = (char *)(stack->data[i]);
        //printf("%p\n", a);
        printf("%s\n", (char*)(stack->data[i]));
    }
    return 0;
}

int push(CStack* stack, char* newData) {
    if(newData == NULL) {
        return -2;
    }
    if(stack->pos == stack->size) {
        if(enlargeStack(stack) == NULL) {
            printf("ERROR: Enlargement Failed, Probably Because of Insufficient Memory.\n");
            printf("Exiting Now...\n");
            return -1;
        }
    }
    char *p = stack->data + stack->pos * (sizeof(char *));
    *p = newData;
    stack->pos++;
    return 0;
}

int main(void) {
    char inData[100] = {'\0'};
    CStack* stack =  (CStack *)malloc(sizeof(CStack));
    initStack(stack);
    while(1) {
        scanf("%s", inData);
        push(stack, inData);
        printAll(stack);
    }
}