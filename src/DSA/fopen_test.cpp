#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void bubble_sort(int a[], int n) {
    int i, j, t;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
}
void print(int a[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
}
int SelectMin(int a[], int i) {
    int min;
    int j, k;
    k = i;
    min = a[i];
    for (j = i + 1; j < 10000; j++) {
        if (a[j] < min) {
            k = j;
            min = a[j];
        }
    }
    return k;
}

void SelectSort(int a[]) {
    int i, j, t;
    for (i = 0; i < 10000; i++) {
        j = SelectMin(a, i);
        if (i != j) {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
}

void InsertSort(int a[]) {
    int i, j;
    for (i = 2; i <= 10000; i++) {
        if (a[i] < a[i - 1]) {
            a[0] = a[i];
            for (j = i - 1; a[0] < a[j]; --j)
                a[j + 1] = a[j];
            a[j + 1] = a[0];
        }
    }
}
int main() {
    srand((unsigned)time(NULL));
    FILE *fp = fopen("intfile.txt", "w");
    if (fp == NULL) return 0;
    int i;
    for (i = 0; i < 10000; i++) {
        fprintf(fp, "%d ", rand() / 100);
    }
    fclose(fp);
    int b[10000] = {0};
    FILE *fpRead = fopen("intfile.txt", "r");
    if (fp == NULL) {
        return 0;
    }
    for (i = 0; i < 10000; i++) {
        fscanf(fpRead, "%d", &b[i]);
        printf("%d ", b[i]);
    }
    int a[13];
    a[0] = {0};
    for (i = 1; i < 13; i++) {
        a[i] = b[i - 1];
    }

    int c[10000];
    for (i = 0; i < 10000; i++) {
        c[i] = b[i];
    }
    printf("\n\n");
    printf("插入排序前：");
    for (i = 1; i < 13; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("插入排序后：");
    InsertSort(a);
    for (i = 1; i < 13; i++) {
        printf("%d ", a[i]);
    }

    printf("\n\n");
    printf("冒泡排序前：");
    print(b, 10000);
    printf("\n");
    printf("冒泡排序后：");
    bubble_sort(b, 10000);
    print(b, 10000);

    printf("\n\n");
    printf("选择排序前：");
    print(c, 10000);
    printf("\n");
    printf("选择排序后：");
    SelectSort(c);
    print(c, 10000);
}
