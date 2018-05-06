//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 1e4 + 5;
const int lgN  = 15;
struct Tree {
    struct Node : vector<Node*> {
        int dep;
        Node* pa[(int)lgN];
        Node() { clear(), dep = -1; }
    }_memN[MAXN], *node[MAXN], *rt;
    int V;
    Tree(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
    }
    inline void addEdge(int u, int v) {
        node[u]->push_back(node[v]);
        node[v]->push_back(node[u]);
    }
    void solve(int _rt) {
        rt = node[_rt];
        dfs(rt, rt, 0);
    }
    void dfs(Node *u, Node *p, int dep) {
        u->pa[0] = p; u->dep = dep;
        for (int i = 1 ; i < lgN ; i++)
            u->pa[i] = u->pa[i - 1]->pa[i - 1];
        //for (auto v : *u)
        for (vector<Node*>::iterator it = u->begin() ; it != u->end() ; it++) {
            Node *v = *it;
            if (!~v->dep)
                dfs(v, u, dep + 1);
        }
    }
    int query(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        if (u->dep < v->dep) swap(u, v);
        for (int i = lgN - 1 ; ~i ; i--)
            if (u->pa[i]->dep >= v->dep)
                u = u->pa[i];
        if (u == v) return u - _memN + 1;
        for (int i = lgN - 1 ; ~i ; i--)
            if (u->pa[i] != v->pa[i])
                u = u->pa[i], v = v->pa[i];
        return u->pa[0] - _memN + 1;
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        Tree *T = new Tree(n);
        int in_deg[MAXN]; memset(in_deg, 0, sizeof(in_deg));
        for (int i = 0 ; i < n - 1 ; i++) {
            int u, v; cin >> u >> v;
            T->addEdge(u - 1, v - 1); in_deg[v - 1]++;
        }
        int rt = -1;
        for (int i = 0 ; i < n ; i++)
            if (in_deg[i] == 0) {
                rt = i; break;
            }
        T->solve(rt);
        int u, v; cin >> u >> v;
        cout << T->query(u - 1, v - 1) << '\n';
        delete T;
    }
}

