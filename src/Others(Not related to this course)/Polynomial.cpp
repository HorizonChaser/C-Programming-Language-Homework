#include<stdio.h>
#include<malloc.h>
//���ӷ� 
//�����Ⱑ 
typedef struct LinkListNode{
	int cimi;
	int xishu;
	struct LinkListNode *next;
}node;

node *create(){
	node *head = (node *)malloc(sizeof(node));
	head->next = NULL;
	head->xishu = 0;
	node *t = head;
	int i,x,y;
	scanf("%d",&i);
	head->cimi = i;
	while(i){
		node *p = (node *)malloc(sizeof(node));
		scanf("%d",&x);
		scanf("%d",&y); 
		p->xishu = x;
		p->cimi = y;
		t->next = p;
		t = t->next;
		t->next = NULL;
		i--;
	}
	return head;
}

node *yunsuan(node *s,node *t){  //�ӵڶ�����ʼ 
	node *p = s;
	node *q = t;
	node *a = (node *)malloc(sizeof(node));
	node *b = a;
	while(q->next && p->next){
		node *c = (node *)malloc(sizeof(node));
		if(p->cimi == q->cimi){
			c->cimi = p->cimi;
			c->xishu = p->xishu + q->xishu;
			p = p->next;
			q = q->next;
		}else{
			if(q->cimi < p->cimi){
				c->cimi = q->cimi;
				c->xishu = q->xishu;
				q = q->next;
			}else{
				c->cimi = p->cimi;
				c->xishu = p->xishu;
				p = p->next;
			}
		}
		b->next = c;
		c->next = NULL;
		b = b->next;
	}
	while(p->next){
		node *c = (node *)malloc(sizeof(node));
		c->cimi = p->cimi;
		c->xishu = p->xishu;
		b->next = c;
		c->next = NULL;
		b = b->next;
		p = p->next;
	}
	while(q->next){
		node *c = (node *)malloc(sizeof(node));
		c->cimi = q->cimi;
		c->xishu = q->xishu;
		b->next = c;
		c->next = NULL;
		b = b->next;
		q = q->next;
	}
	return a;
}

void print(node *t){
	node *p = t;
	while(p->next){
		printf("%d %d\n",p->xishu,p->cimi);
	}
}

int main()
	{
		node *p = (node *)malloc(sizeof(node));
		p = create();
		node *q = (node *)malloc(sizeof(node));
		q = create();
		node *t = (node *)malloc(sizeof(node));
		t = yunsuan(p->next,q->next);
		print(t);
		return 0;
	}
