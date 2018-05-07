#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e4 + 5;
const int MAXM = 260000 + 5;
const int lgN  = __lg(MAXN) + 5;
const int INF = 0x3f3f3f3f;
struct Tree {
    struct Node; struct Edge; int V, totalW;
    struct Node : vector<Edge*> {
        Node *pa[lgN]; int w[lgN], dep;
    }_memN[MAXN], *node[MAXN], *rt;
    struct Edge {
        Node *u, *v; int w;
        Edge(Node *_u, Node *_v, int _w) {
            u = _u; v = _v; w = _w;
        }
        Edge(){}
    }_memE[MAXM], *ptr;
    Tree(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
        totalW = 0; ptr = _memE;
        rt = node[0];
    }
    void addEdge(int u, int v, int w) {
        node[u]->push_back(new (ptr++) Edge(node[u], node[v], w));
        node[v]->push_back(new (ptr++) Edge(node[v], node[u], w));
    }
    void dfs(Node *u, Node *p, int w, int dep) {
        u->pa[0] = p; u->w[0] = w; u->dep = dep;
        for (int i = 1 ; i < lgN ; i++) {
            u->pa[i] = u->pa[i - 1]->pa[i - 1];
            u->w[i] = max(u->w[i - 1], u->pa[i - 1]->w[i - 1]);
        }
        for (auto e : *u) 
            if (e->v != p)
                dfs(e->v, u, e->w, dep + 1);
    }
    int query(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        int ans = -1;
        if (u->dep < v->dep) swap(u, v);
        for (int i = lgN - 1 ; ~i ; i--) 
            if (u->pa[i]->dep >= v->dep)
                ans = max(ans, u->w[i]), u = u->pa[i];
        if (u == v) return ans;
        for (int i = lgN - 1 ; ~i ; i--)
            if (u->pa[i] != v->pa[i])
                ans = max({ans, u->w[i], v->w[i]}),
                    u = u->pa[i], v = v->pa[i];
        return ans = max({ans, u->w[0], v->w[0]});
    }
};
struct DisjointSet {
    int n; vector<int> pa;
    DisjointSet(int _n) {
        n = _n; pa.resize(n + 1, -1);
    }
    int find(int p) {
        return pa[p] < 0 ? p : pa[p] = find(pa[p]);
    }
    bool _union(int u, int v) {
        int x = find(u), y = find(v);
        if (x != y) {
            if (pa[x] < pa[y]) swap(x, y);
            pa[y] += pa[x], pa[x] = y;
        }
        return x != y;
    }
};
struct Graph {
    struct Edge {
        int u, v, w; bool inT;
        Edge(int _u, int _v, int _w) {
            u = _u, v = _v, w = _w; inT = false;
        }
        bool operator < (const Edge &e) const {
            return w < e.w;
        }
    };
    vector<Edge> e; int n;
    Graph(int _n) : n(_n) { e.clear(); }
    void addEdge(int u, int v, int w) {
        e.push_back(Edge(u, v, w));
    }
    DisjointSet *djs;
    Tree* MST() {
        djs = new DisjointSet(n);
        Tree *res = new Tree(n);
        int cnt = 0;
        sort(e.begin(), e.end());
        for (auto &edge : e) {
            if (djs->_union(edge.u, edge.v)) {
                edge.inT = true;
                res->totalW += edge.w; cnt++;
                res->addEdge(edge.u, edge.v, edge.w);
                if (cnt == n - 1) break;
            }
        }
        delete djs;
        return res;
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        Graph *G = new Graph(n);
        while (m--) {
            int u, v, w; cin >> u >> v >> w;
            G->addEdge(u, v, w);
        }
        Tree *T = G->MST();
        T->dfs(T->rt, T->rt, -1, 0);
        int ans = INF;
        for (auto edge : G->e)
            if (!edge.inT) 
                ans = min(ans, edge.w - T->query(edge.u, edge.v));
        cout << ans << '\n';
        delete T;
    }
}

