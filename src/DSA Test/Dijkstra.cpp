#include <bits/stdc++.h>
using namespace std;

int mapW[16][16], D[16];
bool visited[16] = {false};
int m, n;
const int MAX = 1000000;

int main() {

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            mapW[i][j] = MAX;
        }
        D[i] = MAX;
    }

    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        //cin >> a >> b;
        mapW[a][b] = w;
        //mapW[b][a] = 1;
    }

    //Dijkstra Begin
    string path[16];
    int begin = 1;
    for (int i = 1; i <= m; i++) {
        D[i] = mapW[begin][i];
        //path[i] += to_string(1);
    }
    D[begin] = 0;
    visited[begin] = true;

    for (int cnt = 0; cnt < m - 1; cnt++) {
        int min = MAX, temp;
        for (int i = 1; i <= m; i++) {
            if (visited[i] == false && D[i] < min) {
                min = D[i];
                temp = i;
            }
        }
        visited[temp] = true;
        for (int i = 1; i <= m; i++) {
            if (visited[i] == false && mapW[temp][i] != MAX && (D[temp] + mapW[temp][i]) < D[i]) {
                D[i] = D[temp] + mapW[temp][i];
                path[i] = path[temp] + to_string(i);
            }
        }
    }
    //Dijkstra End

    for (int i = 1; i <= m;i++) {
        cout << "Shortest way to " << i << " = " << path[i] << " ,Length = " << D[i] << endl;
    }
}