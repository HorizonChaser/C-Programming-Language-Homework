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

/*
 *压栈, 返回新元素指针
*/
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

/*
 *弹栈, 返回指向被弹出元素的数据的指针
 */
char *pop(CStack* stack, char* out) {
    CStack *former = stack;
    while(stack->next != NULL){
        stack = stack->next;
    }
    while(former->next != stack) {
        former = former->next;
    }
    out = (char*)malloc(100*sizeof(char));
    memset(out, '\0', 100 * sizeof(char));
    strcpy(out, stack->data);
    former->next = NULL;
    free(stack);
    return out;
}

/*
 *取栈顶元素, 返回指向数据的指针
 */ 
char *top(CStack* stack, char* out) {
    while(stack->next != NULL){
        stack = stack->next;
    }
    out = (char*)malloc(100*sizeof(char));
    memset(out, '\0', 100 * sizeof(char));
    strcpy(out, stack->data);
    return out;
}

/*
 *输出栈
 */
void printAll(CStack* stack) {
    //如果栈的首结点(毕竟是基于链表的实现), 或者首结点的下一节点为空
    //说明栈中没有元素
    if(stack == NULL || (stack = stack->next) == NULL) {
        printf("No Element in the Stack.\n");
        return;
    }
    printf("-----------|Bottom of the Stack|------------\n");
    
    while(stack != NULL) {
        printf("%s\n", stack->data);
        stack = stack->next;//移到下一个元素
    }
    printf("------------|Top of the Stack|--------------\n");
    return;
}

int main(void) {
    char cmd[100];
    char outData[100];
    int num = 0;
    CStack *stack  = (CStack *)malloc(sizeof(CStack));

    if(stack == NULL) {//首结点都分配失败, 大概内存完全没了
        printf("Bad Mem Allocate...Exiting Now...");
        return -1;
    }
    stack->next = NULL;
    stack->data = "First Node with SRBK";

    printf("------|C_Stack based on LinkedList by HorizonChaser|------\n");
    printf("Supported Commands: \n");
    printf("\tPUSH\n\t[DATA]\n  and\n\tPOP\n  and\n\tTOP\n");
    printf("----------------------------------------------------------\n");
    printf("Note that POP will show AND delete the element on the top\nWhile TOP will ONLY show the element on the top\nAnd Data Length is 100 chars\n");
    //printf("Input Your Command in the Next Line\n");
    printf("----------------------------------------------------------\n");

    
    while(1) {
        scanf("%s", cmd);
        if(strcmp(cmd, "PUSH") == 0) {
            scanf("%s", outData);

            if(push(stack, outData) != NULL){
                printf("Successfully Pushed. All Elements Are As Follows.\n");
                printAll(stack);
                num++;
            }
        }

        else if(strcmp(cmd, "POP") == 0) {
            if(num == 0) {
                printf("No Element in the Stack.\n");
                continue;
            }
            char* popped = pop(stack, outData);
            num--;
            printf("The Element Below Has Been Successfully Popped:\n");
            printf("%s\n", popped);
            printf("All Elements Are As Follows.\n");
            printAll(stack);
        }

        else if(strcmp(cmd, "TOP") == 0) {
            if(num == 0) {
                printf("No Element in the Stack.\n");
                continue;
            }
            char *topper = top(stack, outData);
            printf("The Element Below is on the Top of the Stack:\n");
            printf("%s\n", topper);
        }

        else if(strcmp(cmd, "EXIT") == 0) {
            printf("Exiting Now...");
            return 0;
        }

        else {
            printf("Unrecongized Invalid Command: %s\n", cmd);
        }

        memset(cmd, '\0', sizeof(cmd));
        memset(outData, '\0', sizeof(outData));
        system("pause");
    }
    return 0;
}


