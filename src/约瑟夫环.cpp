#include <iostream>
using namespace std;
int a[100];
int m, n;
typedef struct Node
{
    int data;
    int id;
    struct Node *next;
}node, *linklist;
void creatLinklist(linklist &L)
{
    linklist p, q;
    L = new node();
    L->next = NULL;
    L->data = 0;  //���׽ڵ�����Ϊ0
    p = L;
    for(int i = 0; i<n; i++)
    {
        q = new node();
        q->data = a[i];
        q->id = i+1;  //��Ϊi��0��ʼ
        q->next = NULL;
        p->next = q;
        p = q;
    }
    p->next = L;
}
void choose(linklist &L)
{
    linklist p, q;
    //p��ʾҪ����Ԫ�ص�ǰ����q��ʾҪ���е�Ԫ��
    p = L;
    q = L->next;
    int cnt = m;
    while(p)
    {
        //��ȡ��
        if(cnt == 1 && q->data != 0)
        {
           p->next = q->next;  //�ı���
           cnt = q->data;  //�ı�����
           cout<<q->id<<" ";  
           q = q->next;  //�����ƶ�һ����λ
        }
        //����ȡ��
        else
        {
            if(q->data != 0)  //�����׽ڵ�
                cnt--;
            p = p->next;
            q = q->next;
        }
    }
}
int main()
{
    cin>>m>>n;
    for(int i = 0; i<n; i++)
        cin>>a[i];
    linklist L;
    creatLinklist(L);
    choose(L);
    return 0;
}
