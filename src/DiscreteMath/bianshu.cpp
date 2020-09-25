#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int main() {
    int p, q;
    //printf("请输bai入p和q的真值\n");
    cin >> p >> q;

    if (p == 1 && q == 1)
        printf("1\n");//合取
    else
        printf("0\n");
    if (p == 1 || q == 1)
        printf("1\n");//析取
    else
        printf("0\n");
    if (p == 1 && q == 0)
        printf("0\n");//条件
    else
        printf("1\n");
    if (p == q)
        printf("1\n");//双条件
    else
        printf("0\n");
}