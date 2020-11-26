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
    L->data = 0;  //设首节点密码为0
    p = L;
    for(int i = 0; i<n; i++)
    {
        q = new node();
        q->data = a[i];
        q->id = i+1;  //因为i从0开始
        q->next = NULL;
        p->next = q;
        p = q;
    }
    p->next = L;
}
void choose(linklist &L)
{
    linklist p, q;
    //p表示要出列元素的前驱，q表示要出列的元素
    p = L;
    q = L->next;
    int cnt = m;
    while(p)
    {
        //能取到
        if(cnt == 1 && q->data != 0)
        {
           p->next = q->next;  //改变后继
           cnt = q->data;  //改变密码
           cout<<q->id<<" ";  
           q = q->next;  //往后移动一个单位
        }
        //不能取到
        else
        {
            if(q->data != 0)  //跳过首节点
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
