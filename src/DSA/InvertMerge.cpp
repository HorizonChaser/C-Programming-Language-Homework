// 归并递减
#include <malloc.h>
#include <stdio.h>
//单链表结构类型定义
typedef int datatype;
typedef struct node {
    datatype data;
    struct node* next;
} linklist;

linklist* create();
void print(linklist*);
linklist* mergelist(linklist*, linklist*);
void insert(linklist*, linklist*);
int main() {
    linklist *La, *Lb, *Lc;
    La = create();
    Lb = create();
    printf("La:");
    print(La);
    printf("Lb:");
    print(Lb);
    Lc = mergelist(La, Lb);
    printf("Lc:");
    print(Lc);
}

linklist* mergelist(linklist* La, linklist* Lb) {
    linklist *temp, *currA = La->next, *currB = Lb->next; //当前节点
    La->next = NULL;                                    //结果链表
    while (currA && currB) {
        if (currA->data <= currB->data) {
            temp = currA->next;
            currA->next = La->next;
            La->next = currA;  //头插法
            currA = temp;
        } else {
            temp = currB->next;
            currB->next = La->next;
            La->next = currB;
            currB = temp;
        }
    }
    if (currA)
        currB = currA;//处理剩下的部分
    while (currB) {
        temp = currB->next; //头插法
        currB->next = La->next;
        La->next = currB;
        currB = temp;
    }
    return La;
}