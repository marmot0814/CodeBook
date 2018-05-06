#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int lgN  = __lg(MAXN) + 5;
const int INF = 0x3f3f3f3f;
struct Tree {
    struct Node : vector<Node*>{
        int dep, v;
        Node* pa[lgN];
        int maxV[lgN];
        Node() { 
            clear(), dep = -1;
            for (int i = 0 ; i < lgN ; i++)
                maxV[i] = -INF;
        }
    }_memN[MAXN], *node[MAXN];
    int V;
    Tree(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
    }
    inline void addEdge(int u, int v) {
        node[u]->push_back(node[v]);
        node[v]->push_back(node[u]);
    }
    void solve() {
        dfs(node[0], node[0], 0);
    }
    void dfs(Node *u, Node *p, int dep) {
        u->pa[0] = p; u->dep = dep;
        u->maxV[0] = max(u->v, p->v);
        for (int i = 1 ; i < lgN ; i++) 
            u->pa[i] = u->pa[i - 1]->pa[i - 1],
            u->maxV[i] = max(u->maxV[i - 1], u->pa[i - 1]->maxV[i - 1]);
        for (auto v : *u) 
            if (!~v->dep)
                dfs(v, u, dep + 1);
    }
    int query(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        int ans = max(u->v, v->v);
        if (u->dep < v->dep) swap(u, v);
        for (int i = lgN - 1 ; ~i ; i--)
            if (u->pa[i]->dep >= v->dep)
                ans = max(ans, u->maxV[i]), u = u->pa[i];
        if (u == v) return ans;
        for (int i = lgN - 1 ; ~i ; i--)
            if (u->pa[i] != v->pa[i])
                ans = max({ans, u->maxV[i], v->maxV[i]}),
                u = u->pa[i], v = v->pa[i];
        return ans = max({ans, u->maxV[0], v->maxV[0]});
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        Tree *T = new Tree(n);
        for (int i = 0 ; i < n - 1 ; i++) {
            int u, v; cin >> u >> v;
            T->addEdge(u - 1, v - 1);
        }
        for (int i = 0 ; i < n ; i++)
            cin >> T->node[i]->v;
        T->solve();
        int q; cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            cout << T->query(u - 1, v - 1) << '\n';
        }
        delete T;
    }
}
