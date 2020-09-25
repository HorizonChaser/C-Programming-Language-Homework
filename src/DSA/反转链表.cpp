#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

//��������ڵ�
typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *Linklist;

//��������
Linklist create() {
    int i, n;  //i��������ѭ��,n���������Ч�ڵ������
    Linklist p, L;
    scanf("%d", &n);
    L = (Linklist)malloc(sizeof(LNode));  // ����һ���������Ч���ݵ�ͷ���
    L->next = NULL;
    for (i = 0; i < n; i++) {
        p = (Linklist)malloc(sizeof(LNode));  //�����½ڵ�
        scanf("%d", &p->data);                //����Ԫ��ֵ
        p->next = L->next;
        L->next = p;
    }
    return L;  //����ͷ�ڵ� ;
}

//����ת���
Linklist ReverseList(Linklist L, int st)  //stΪ1ʱ����������
{
    if (L->next != NULL)
        ReverseList(L->next, 1);

    return L;
}

void put(Linklist L) {
    Linklist p;
    p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    int N;
    scanf("%d", &N);
    Linklist L;
    while (N > 0) {
        L = create();
        ReverseList(L, 0);
        N--;
        put(L);
    }

    return 0;
}
