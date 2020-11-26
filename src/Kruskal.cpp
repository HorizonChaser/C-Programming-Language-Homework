#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int begin, end, weight;
} edge;

typedef struct {
    int val, sign;
} vertex;

int compareEdgesByWeight(const void *a, const void *b) {
    return ((edge *)a)->weight - ((edge *)b)->weight;
}

int getVtxSignByVal(vertex *vtx, int val) {
    return vtx[val].sign;
}

int main() {
    int n, m, ansEdges = 0, ansVtxs = 0;
    cin >> n >> m;
    edge edges[100], minTree[100];
    vertex vtx[100];
    set<int> ansVtx;
    for (int i = 0; i < m; ++i) {
        int _begin, _end, _weight;
        cin >> _begin >> _end >> _weight;
        edges[i].begin = _begin;
        edges[i].end = _end;
        edges[i].weight = _weight;
    }
    for (int i = 0; i < n; ++i) {
        vtx[i].val = vtx[i].sign = i;
    }

    qsort(edges, m, sizeof(edge), compareEdgesByWeight);

    for (int i = 0; i < m; ++i) {
        if (ansVtxs == n)
            break;
        if (getVtxSignByVal(vtx, edges[i].begin) == getVtxSignByVal(vtx, edges[i].end)) {
            continue;
        } else {
            minTree[ansEdges++] = edges[i];
            ansVtx.insert(edges[i].begin);
            ansVtx.insert(edges[i].end);
            /*
            minTree[ansEdges].begin = edges[i].begin;
            minTree[ansEdges].end = edges[i].end;
            minTree[ansEdges].weight = edges[i].weight;
            ansEdges++;
            */

            ansVtxs++;

            /*
            int ee = edges[i].end, eb = edges[i].begin;
            vtx[ee].sign = vtx[eb].sign;
            */

            set<int>::iterator ansVtxIter = ansVtx.begin();
            while (ansVtxIter != ansVtx.end()){
                for (int k = 0; k < ansEdges; ++k) {
                    if (minTree[k].end == *ansVtxIter) {
                        vtx[*ansVtxIter].sign = vtx[minTree[k].begin].sign;
                    }

                }
                for (int k = 0; k < ansEdges; ++k) {
                    if (minTree[k].begin == *ansVtxIter) {
                        vtx[*ansVtxIter].sign = vtx[minTree[k].end].sign;
                    }

                }
                ansVtxIter++;
            }
        }
    }

    for (int i = 0; i < ansEdges; ++i) {
        int a = minTree[i].begin, b = minTree[i].end, c = minTree[i].weight;
        if (a < b)
            cout << a << " " << b << " " << c;
        else
            cout << b << " " << a << " " << c;
        cout << endl;
    }

    return 0;
}
