#include <bits/stdc++.h>
using namespace std;
struct DisjointSet{
    int n;
    vector<int> pa;
    DisjointSet(int _n){
        n = _n;
        pa.resize(n + 1, -1);
    }
    int find(int p){
        return pa[p] < 0 ? p : pa[p] = find(pa[p]);
    }
    bool Union(int u, int v){
        int x = find(u), y = find(v);
        if (x != y){
            if (pa[x] < pa[y]) swap(x, y);
            pa[y] += pa[x], pa[x] = y;
        }
        return x != y;
    }
};
struct Graph {
    int V;
    struct Edge {
        int u, v, w;
        Edge(int _u, int _v, int _w) 
            : u(_u), v(_v), w(_w) {}
        bool operator < (const Edge &rhs) const {
            return w < rhs.w;
        }
    };
    Graph(int _V) : V(_V) {}
    vector<Edge> _memE;
    DisjointSet *djs;
    void addEdge(int u, int v, int w) {
        _memE.push_back(Edge(u, v, w));
    }
    int MST() {
        sort(_memE.begin(), _memE.end());
        djs = new DisjointSet(V);
        int res = 0, cnt = 0;
        for (auto e : _memE) {
            if (djs->Union(e.u, e.v)) 
                res += e.w, cnt++;
            if (cnt == V - 1) break;
        }
        delete djs;
        return res;
    }
};
int main() {
    int n, m; cin >> n >> m;
    Graph *G = new Graph(n);
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        G->addEdge(u - 1, v - 1, w);
    }
    cout << G->MST() << '\n';
}
