#include<cstdio>
#include<iostream>
#include<stack>

using namespace std;
struct base {
    int x, y, dir;
};
int d[4][2] = {{0,  1},
               {1,  0},
               {0,  -1},
               {-1, 0}};    //依据题意先后搜索的四个方向，右，下，左，上
stack<base> s;
int m, n, a[1000][1000];  //在main函数外定义a[1000][1000]不然内存不够
int startx, starty, endx, endy;
base now;
int flag = 0; //flag=1表示已经找到终点，不需要在搜索，剪枝想法
void digui() {
    if (flag == 1) {
        return;
    }
    now = s.top();
    for (int i = 0; i < 4; i++) {       //四个边界为特殊情况，要特殊处理
        if (flag == 1) {
            return;
        }
        if (now.x == 1 && i == 3) {
            s.pop();
            digui();
        }
        if (now.x == m && i == 1) {
            continue;
        }
        if (now.y == 1 && i == 2) {
            continue;
        }
        if (now.y == n && i == 0) {
            continue;
        }
        if (a[now.x + d[i][0] - 1][now.y + d[i][1] - 1] == 0) {    //递归和DFS搜索
            a[now.x + d[i][0] - 1][now.y + d[i][1] - 1] = 1;
            now.x += d[i][0];
            now.y += d[i][1];
            now.dir = i + 1;
            s.push(now);
            if (now.x == endx && now.y == endy) {
                flag = 1;
                return;
            } else digui();

        } else if (i == 3 && a[now.x + d[i][0]][now.y + d[i][1]] == 1) {
            s.pop();
            digui();

        }
    }

}

int main() {
    cin >> m >> n;
    cin >> startx >> starty >> endx >> endy;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    now.x = startx;
    now.y = starty;
    now.dir = 0;
    s.push(now);
    digui();

    base e[10000];
    int sum = 0;
    if (s.empty()) {
        cout << "no" << endl;   //没有搜到到，输出no
        return 0;
    }
    while (!s.empty()) {  //栈存储的是逆序路径，转化为顺序路径

        e[sum] = s.top();

        sum++;
        s.pop();
    }
    for (int i = sum - 1; i >= 0; i--) {
        if (i != 0)
            cout << "(" << e[i].x << "," << e[i].y << "," << e[i - 1].dir << ")" << ",";
        else
            cout << "(" << e[i].x << "," << e[i].y << "," << e[i].dir << ")";
    }
    return 0;
}