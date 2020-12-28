#include <bits/stdc++.h>

using namespace std;

int main() {
    int m, p, table[105], in = 0, currSize = 0;
    memset(table, -1, 105 * sizeof(int));
    cin >> m >> p;

    while (in != -1) {
        cin >> in;
        if (in == -1)
            return 0;

        int key = in % p;

        int flag = 0;
        for (int i = 0; i < 105; i++) {
            if (table[i] == in) {
                flag = 1;
                cout << i << endl;
                break;
            }
        }
        if(flag == 1)
            continue;
        if (flag == 0) {
            if (currSize == m - 1) {
                cout << "Table full" << endl;
                return 0;
            }
        }

        if (table[key] == -1) {
            currSize++;
            table[key] = in;
            cout << key << endl;
            continue;
        } else {
            for (int d = 1; d <= m - 1; d++) {
                int newKey = (d + key) % m;
                if (table[newKey] == -1) {
                    table[newKey] = in;
                    currSize++;
                    cout << newKey << endl;
                    break;
                }
            }
        }
    }
    return 0;
}