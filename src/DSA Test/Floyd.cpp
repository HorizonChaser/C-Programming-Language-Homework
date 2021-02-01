#include <bits/stdc++.h>
using namespace std;

int mapW[16][16], D[16][16];
string P[16][16];
bool visited[16] = {false};
int m, n;
const int MAX = 1000000;

int main() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            mapW[i][j] = MAX;
            D[i][j] = MAX;
        }
    }

    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        //cin >> a >> b;
        mapW[a][b] = w;
        //mapW[b][a] = 1;

        D[a][b] = w;
        P[a][b] = to_string(b);
    }

    for (int u = 0; u < m; u++) {
        for (int v = 0; v < m; v++) {
            for (int w = 0; w < m; w++) {
                if (D[v][u] + D[u][w] < D[v][w]) {
                    D[v][w] = D[v][u] + D[u][w];
                    P[v][w] = P[v][u] + P[u][w];
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << D[i][j] << " # ";
        }
        cout << endl;
    }

    cout << " -------------------------- " << endl;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << P[i][j] << " # ";
        }
        cout << endl;
    }
}