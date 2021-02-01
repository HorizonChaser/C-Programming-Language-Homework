#include <bits/stdc++.h>
using namespace std;

int main() {
    int i = 42;

    int &r = i;
    const int &r2 = r + i;
    i++;
    cout << r << " " << r2 << endl;
    cout << i << endl;

    double dval = 3.14;
    const int &ri = dval;
}