#include <bits/stdc++.h>
using namespace std;

int mapW[16][16] = {0};
bool visited[16] = {false};
int m, n;

void visit(int v) {
    cout << v << endl;
}

void printVis() {
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < 16; i++)
        cout << visited[i] << " ";
    cout << endl;
    cout << "-----------------------------------" << endl;
}

void DFS(int v) {
    visited[v] = true;
    visit(v);
    for (int w = 1; w <= m; w++) {
        if (mapW[v][w] != 0) {
            if (visited[w] == false) {
                DFS(w);
            }
        }
    }
}

void BFS(int v) {
    queue<int> queue;
    for (int i = 1; i <= m; i++) {
        if (visited[i] == false) {
            visited[i] = true;
            visit(i);
            queue.push(i);
        }
        while (queue.empty() == false) {
            int v = queue.front();
            queue.pop();
            for (int w = 1; w <= m; w++) {
                if (mapW[v][w] != 0) {
                    if (visited[w] == false) {
                        visited[w] = true;
                        visit(w);
                        queue.push(w);
                    }
                }
            }
        }
    }
}

int main() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int a, b, w;

        // cin >> a >> b >> w;
        cin >> a >> b;

        mapW[a][b] = 1;
        mapW[b][a] = 1;
    }

    cout << "------" << endl;

    for (int i = 1; i <= m; i++) {
        if (visited[i] == false) {
            DFS(i);
        }
    }
    cout << "------" << endl;
    for (int i = 0; i < 16; i++)
        visited[i] = false;

    BFS(1);
}