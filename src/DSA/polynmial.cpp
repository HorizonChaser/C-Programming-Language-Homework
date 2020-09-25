#include <malloc.h>
#include <stdio.h>

typedef struct node {
    float coef;
    int expn;
    struct node *next;
} Lnode, *polynmial;

void creat(polynmial &L);
void display(polynmial L);
void sort(polynmial &L);
void reverse(polynmial &L);
void add(polynmial La, polynmial Lb, polynmial &Lc);
void subtract(polynmial La, polynmial Lb, polynmial &Ld);

void creat(polynmial &L) {
    int i, n;
    static struct node *p;
    scanf("%d", &n);
    L = (struct node *)malloc(sizeof(struct node));
    L->next = NULL;
    for (i = 0; i < n; i++) {
        p = (struct node *)malloc(sizeof(struct node));
        scanf("%f %d", &p->coef, &p->expn);
        p->next = L->next;
        L->next = p;
    }
}
void display(polynmial L) {
    struct node *p, *q;
    int flag = 0;
    int k = 0;
    q = L->next;
    while (q) {
        if (q->coef != 0)
            k++;
        q = q->next;
    }
    printf("%d+ ", k);
    p = L->next;
    if (p->coef != 0) {
        printf("%.1fx^%d+ ", p->coef, p->expn);
        flag++;
    }
    for (p = p->next; p; p = p->next) {
        if (p->coef != 0) {
            printf("%.1fx^%d+ ", p->coef, p->expn);
            flag++;
        }
    }
    if (flag == 0)
        printf("%d\n", flag);
    else
        printf("\n");
}
void sort(polynmial &L) {
    polynmial p, q, r, u;
    p = L->next;
    L->next = NULL;
    while (p != NULL) {
        r = L;
        q = L->next;
        while ((q != NULL) && (q->expn <= p->expn)) {
            r = q;
            q = q->next;
        }
        u = p->next;
        r->next = p;
        p->next = q;
        p = u;
    }
}
void reverse(polynmial &L) {
    polynmial H;
    static struct node *p, *q, *s;
    H = (struct node *)malloc(sizeof(struct node));
    H->next = NULL;
    p = (struct node *)malloc(sizeof(struct node));
    s = L->next;
    p->coef = s->coef;
    p->expn = s->expn;
    p->next = s->next;
    while (s) {
        p->coef = s->coef;
        p->expn = s->expn;
        p->next = s->next;
        q = H->next;
        H->next = p;
        p->next = q;
        p = (struct node *)malloc(sizeof(struct node));
        s = s->next;
    }
    p = H->next;
    q = L->next;
    while (p) {
        q->coef = p->coef;
        q->expn = p->expn;
        q = q->next;
        p = p->next;
    }
}
void add(polynmial La, polynmial Lb, polynmial &Lc) {
    struct node *pa, *pb;
    static struct node *pc;
    Lc = (struct node *)malloc(sizeof(struct node));
    pa = La->next;
    pb = Lb->next;
    pc->next = NULL;
    while (pa && pb) {
        pc = (struct node *)malloc(sizeof(struct node));
        if (pa->expn < pb->expn) {
            pc->next = Lc->next;
            Lc->next = pc;
            pc->coef = pa->coef;
            pc->expn = pa->expn;
            pa = pa->next;
        } else {
            if (pa->expn == pb->expn) {
                pc->next = Lc->next;
                Lc->next = pc;
                pc->expn = pa->expn;
                pc->coef = pa->coef + pb->coef;
                pa = pa->next;
                pb = pb->next;

            } else {
                pc->next = Lc->next;
                Lc->next = pc;
                pc->coef = pb->coef;
                pc->expn = pb->expn;
                pb = pb->next;
            }
        }
        while (pa) {
            pc = (struct node *)malloc(sizeof(struct node));
            pc->next = Lc->next;
            Lc->next = pc;
            pc->coef = pa->coef;
            pc->expn = pa->expn;
            pa = pa->next;
        }
        while (pb) {
            pc = (struct node *)malloc(sizeof(struct node));
            pc->next = Lc->next;
            Lc->next = pc;
            pc->coef = pb->coef;
            pc->expn = pb->expn;
            pb = pb->next;
        }
    }
}

void subract(polynmial La, polynmial Lb, polynmial &Ld) {
    struct node *pa, *pb;
    static struct node *pd;
    Ld = (struct node *)malloc(sizeof(struct node));
    pa = La->next;
    pb = Lb->next;
    Ld->next = NULL;
    while (pa && pb) {
        pd = (struct node *)malloc(sizeof(struct node));
        if (pa->expn < pb->expn) {
            pd->next = Ld->next;
            Ld->next = pd;
            pd->coef = pa->coef;
            pd->expn = pa->expn;
            pa = pa->next;
        } else {
            if (pa->expn == pb->expn) {
                pd->next = Ld->next;
                Ld->next = pd;
                pd->expn = pa->expn;
                pd->coef = pa->coef - pb->coef;
                pa = pa->next;
                pb = pb->next;
            } else {
                pd->next = Ld->next;
                Ld->next = pd;
                pd->coef = pb->coef;
                pd->expn = pb->expn;
                pb = pb->next;
            }
        }
        while (pa) {
            pd = (struct node *)malloc(sizeof(struct node));
            pd->next = Ld->next;
            Ld->next = pd;
            pd->coef = pa->coef;
            pd->expn = pa->expn;
            pa = pa->next;
        }
        while (pb) {
            pd = (struct node *)malloc(sizeof(struct node));
            pd->next = Ld->next;
            Ld->next = pd;
            pd->coef = -pb->coef;
            pd->expn = pb->expn;
            pb = pb->next;
        }
    }
}
int main() {
    int sign;
    polynmial La, Lb, Lc, Ld;
    creat(La);
    creat(Lb);
    scanf("%d", &sign);
    sort(La);
    sort(Lb);
    switch (sign) {
        case 0:
            add(La, Lb, Lc);
            sort(Lc);
            reverse(Lc);
            display(Lc);
            break;
        default:
            subract(La, Lb, Ld);
            sort(Ld);
            reverse(Ld);
            display(Ld);
            break;
    }
    return 0;
}
