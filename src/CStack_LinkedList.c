#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * C-style Stack, based on Linked List
 * C语言栈实现, 基于链表(单链表)
*/
typedef struct CStack {
    char *data;//数据域
    struct CStack *next; //指针域
}CStack;

CStack *push(CStack* stack, char* inData) {
    if(inData == NULL)
        return NULL;
    CStack *newNode = (CStack *)malloc(sizeof(CStack));
    if(newNode == NULL)
        return NULL;
    while(stack->next != NULL)
        stack = stack->next;
    stack->next = newNode;
    newNode->next = NULL;
    char* newData = (char*)malloc(100*sizeof(char));
    strcpy(newData, inData);
    newNode->data = newData;
    return newNode;
}

CStack *pop(CStack* stack, char* out) {
    CStack *former = stack;
    while(stack->next != NULL){
        stack = stack->next;
    }
    while(former->next != stack) {
        former = former->next;
    }
    char* cpy = (char*)malloc(100*sizeof(char));
    out = cpy;
    memcpy(out, stack->data, 100*sizeof(char));
    former->next = NULL;
    free(stack);
    return former;
}

void printAll(CStack* stack) {
    if(stack == NULL) {
        printf("No Element in the Stack.\n");
        return;
    }
    printf("-----------|Bottom of the Stack|------------\n");
    while(stack != NULL) {
        printf("%s\n", stack->data);
        stack = stack->next;
    }
    printf("------------|Top of the Stack|--------------\n");
    return;
}

int main(void) {
    char cmd[100];
    char outData[100];
    int num = 0;
    CStack *stack  = (CStack *)malloc(sizeof(CStack));

    if(stack == NULL) {
        printf("Bad Mem Allocate...Exiting Now...");
        return -1;
    }
    stack->next = NULL;
    stack->data = "Initial";

    printf("Supported Commands: \n");
    printf("\tPUSH\n\t[DATA]\n  and\n\tPOP\n  and\n\tTOP\n");
    printf("Note that POP will show AND delete the element on the top\nWhile TOP will ONLY show the element on the top\n\n");
    printf("Input Your Command: ");

    
    while(strcmp(cmd, "EXIT") != 0) {
        scanf("%s", cmd);
        if(strcmp(cmd, "PUSH") == 0) {
            printf("Please Input Data, Max Length 100 chars: ");
            scanf("%s", outData);

            if(push(stack, outData) != NULL){
                printf("Successfully Pushed. All Elements Are As Follows.\n");
                printAll(stack);
                num++;
            }
            memset(cmd, '\0', sizeof(cmd));
            memset(outData, '\0', sizeof(outData));
            continue;
        }

        if(strcmp(cmd, "POP") == 0) {
            if(num == 0) {
                printf("No Element in the Stack.\n");
                continue;
            }
            pop(stack, outData);
            num--;
            printf("%s\n", outData);
            printf("Successfully Popped. All Elements Are As Follows.\n");
            printAll(stack);

            memset(cmd, '\0', sizeof(cmd));
            memset(outData, '\0', sizeof(outData));
            continue;
        }
    }
    return 0;
}


