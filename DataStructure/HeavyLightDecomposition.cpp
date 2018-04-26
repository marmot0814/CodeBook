#include <bits/stdc++.h>
using namespace std;
#define PB push_back
const int MAXN = 1e3 + 5;
struct Tree{
    struct Node; struct Edge; int V;
    struct Node : vector<Node*> {
        int sz, dep, v, id;
        Node *pa, *top, *hc;
    }_memN[MAXN], *node[MAXN], *rt;
    Tree(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++) 
            node[i] = _memN + i;
        rt = node[0];
    }
    void addEdge(int u, int v) {
        node[u]->push_back(node[v]);
        node[v]->push_back(node[u]);
    }

    int stamp;
    void HLD() {
        stamp = 0;
        dfs_size(rt);
        dfs_link(rt, rt);
    }
    void dfs_size(Node *u) {
        u->sz = 1; u->hc = NULL;
        for (auto v : *u) {
            if (v == u->pa) continue;
            v->pa = u;
            v->dep = u->dep + 1;
            dfs_size(v);
            if (!u->hc || v->sz > u->hc->sz)
                u->hc = v;
            u->sz += v->sz;
        }
    }
    void dfs_link(Node *u, Node *_top) {
        u->id = stamp++;
        u->top = _top;
        if (!u->hc) return ;
        dfs_link(u->hc, _top);
        for (auto v : *u) {
            if (v == u->hc || v == u->pa) continue;
            dfs_link(v, v);
        }
    }
    void Print() {
        cout << "\tid\tsz\tdep\tpa\ttop\thc\n";
        for (int i = 0; i < V ; i++) {
            Node *u = node[i];
            cout << "G[" << i << "]:\t" << u->id << '\t' << u->sz
                << '\t' << u->dep << '\t' << ( u->pa ? u->pa - _memN : -1 )
                << '\t' << ( u->top ? u->top - _memN : -1 ) << '\t'
                << ( u->hc ? u->hc - _memN : -1 ) << '\n';
        }
    }
    Node* query(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        Node *uTop = u->top, *vTop = v->top;
        while (uTop != vTop) {
            if (uTop->dep < vTop->dep) 
                swap(u, v), swap(uTop, vTop);
            // query [uTop->id, u->id + 1)
            uTop = (u = uTop->pa)->top;
        }
        // if (u != v) query[u->id + 1, v->id + 1)
        return u->dep < v->dep ? u : v; // LCA
    }
};
int main() {
    int n; cin >> n;
    Tree *G = new Tree(n);
    for (int i = 0 ; i < n - 1 ; i++){
        int u, v; cin >> u >> v;
        G->addEdge(u, v);
    }
    G->HLD();
    G->Print();
}
