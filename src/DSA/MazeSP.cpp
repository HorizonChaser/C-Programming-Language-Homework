#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct status {
    int i, j;  //坐标
    int heading;   //当前位置下一方向
} status;

typedef struct LinkListNode {
    struct status curr;
    struct LinkListNode *next;
} * SLinkList;

SLinkList A;
SLinkList Stack;

void push(SLinkList &Stack, status curr) {
    SLinkList p = (SLinkList)malloc(sizeof(LinkListNode));
    if (!p)
        exit(-1);
    p->curr = curr;
    p->next = Stack;
    Stack = p;
}

void pop(SLinkList &Stack) {
    if (Stack == NULL) exit(0);
    SLinkList p = Stack;
    Stack = Stack->next;
    free(p);
}

void sw(SLinkList &Stack, SLinkList &A) {
    SLinkList p = Stack;
    while (p != NULL) {
        push(A, p->curr);
        p = p->next;
    }
}

void dumpStack(SLinkList &Stack) {
    if (Stack == NULL)
        cout << "no\n";
    else {
        SLinkList p = Stack;
        while (p != NULL) {
            if (p->next == NULL) {
                printf("(%d,%d,1)", p->curr.i, p->curr.j);
                return;
            } else {
                printf("(%d,%d,%d),", p->curr.i, p->curr.j, p->curr.heading);
                p = p->next;
            }
        }
    }
}

void solveMaze(int m, int n, int xBegin, int yBegin, int xEnd, int yEnd, int num[600][600]) {
    A = NULL;
    Stack = NULL;
    status currPos;
    currPos.i = xBegin;
    currPos.j = yBegin;
    currPos.heading = 0;
    push(Stack, currPos);

    while (Stack && (Stack->curr.i != xEnd || Stack->curr.j != yEnd)) {
        Stack->curr.heading++;
        if (Stack->curr.heading == 1 && (Stack->curr.j < n + 1)) {
            if (num[Stack->curr.i][Stack->curr.j + 1] == 0) {
                num[Stack->curr.i][Stack->curr.j] = -1;
                status newPos;
                newPos.i = Stack->curr.i;
                newPos.j = Stack->curr.j + 1;
                newPos.heading = 0;
                push(Stack, newPos);
            }
        } else if (Stack->curr.heading == 2 && (Stack->curr.i < m + 1) && num[Stack->curr.i + 1][Stack->curr.j] == 0) {
            status newPos;
            num[Stack->curr.i][Stack->curr.j] = -1;
            newPos.i = Stack->curr.i + 1;
            newPos.j = Stack->curr.j;
            newPos.heading = 0;
            push(Stack, newPos);
        } else if (Stack->curr.heading == 3 && Stack->curr.j >= 1 && num[Stack->curr.i][Stack->curr.j - 1] == 0) {
            status newPos;
            num[Stack->curr.i][Stack->curr.j] = -1;
            newPos.i = Stack->curr.i;
            newPos.j = Stack->curr.j - 1;
            newPos.heading = 0;
            push(Stack, newPos);
        } else if (Stack->curr.heading == 4 && Stack->curr.i >= 1 && num[Stack->curr.i - 1][Stack->curr.j] == 0) {
            status newPos;
            num[Stack->curr.i][Stack->curr.j] = -1;
            newPos.i = Stack->curr.i - 1;
            newPos.j = Stack->curr.j;
            newPos.heading = 0;
            push(Stack, newPos);

        } else if (Stack->curr.heading > 4) {
            num[Stack->curr.i][Stack->curr.j] = 1;
            pop(Stack);
        }
    }
    sw(Stack, A);
    dumpStack(A);
}

int main(void) {
    int m = 0, n = 0, xBegin = 0, yBegin = 0, xEnd = 0, yEnd = 0;
    int num[600][600] = {0};
    cin >> m >> n;
    cin >> xBegin >> yBegin;
    cin >> xEnd >> yEnd;

    for (int i = 0; i < m + 2; i++) {
        for (int j = 0; j < n + 2; j++) {
            if (i == 0 || j == 0 || i == m + 1 || j == n + 1)
                num[i][j] = 1;
            else
                cin >> num[i][j];
        }
    }
    solveMaze(m, n, xBegin, yBegin, xEnd, yEnd, num);
    return 0;
}
