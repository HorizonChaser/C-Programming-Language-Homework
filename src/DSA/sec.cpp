#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

#define INF 65535

#define maxn 5005

struct node {
    int x, y, nxt;
    void print() {
        cout << "(" << x << "," << y << "," << nxt << ")";
    }
    node(int xx, int yy, int nxt_ = 0) {
        x = xx, y = yy, nxt = nxt_;
    }
};
int a[maxn][maxn];
int been[maxn][maxn];
int n, m, fromx, fromy, tox, toy;
stack<node> st1;
stack<node> st2;
int main() {
    cin >> n >> m;
    cin >> fromx >> fromy >> tox >> toy;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    st1.push(node(fromx, fromy));
    while (!st1.empty()) {
        st1.top().nxt++;
        node cur = st1.top();
        if (cur.nxt > 4 || !cur.x || !cur.y || cur.x > n || cur.y > m || a[cur.x][cur.y]) {
            //been[cur.x][cur.y]=0;
            st1.pop();
            continue;
        }
        if (cur.x == tox && cur.y == toy) break;
        if (cur.nxt == 1 && !been[cur.x][cur.y + 1]) {
            st1.push(node(cur.x, cur.y + 1));
            been[cur.x][cur.y + 1] = 1;
        } else if (cur.nxt == 2 && !been[cur.x + 1][cur.y]) {
            st1.push(node(cur.x + 1, cur.y));
            been[cur.x + 1][cur.y] = 1;
        }

        else if (cur.nxt == 3 && !been[cur.x][cur.y - 1]) {
            st1.push(node(cur.x, cur.y - 1));
            been[cur.x][cur.y - 1] = 1;
        } else if (cur.nxt == 4 && !been[cur.x - 1][cur.y]) {
            st1.push(node(cur.x - 1, cur.y));
            been[cur.x - 1][cur.y] = 1;
        }
    }
    if (st1.empty()) {
        cout << "no\n";
        return 0;
    }
    while (!st1.empty())
        st2.push(st1.top()), st1.pop();
    while (!st2.empty()) {
        st2.top().print();
        st2.pop();
        if (!st2.empty()) cout << ",";
    }
    cout << endl;
    return 0;
}
