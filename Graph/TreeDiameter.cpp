#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 5;
struct Tree {
    int V;
    struct Node : vector<Node*> {
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
    int diam;
    int diameter() {
        diam = 0;
        dfs(rt, NULL);
        return diam;
    }
    int dfs(Node *u, Node *pa) {
        int h1 = 0, h2 = 0;
        for (auto to : *u) {
            if (pa != to) {
                int h = dfs(to, u) + 1;
                if (h > h1) h2 = h1, h1 = h;
                else if (h > h2) h2 = h;
            }
        }
        diam = max(diam, h1 + h2);
        return h1;
    }
};
int main() {
    int n; cin >> n;
    Tree *G = new Tree(n);
    for (int i = 0 ; i < n - 1 ; i++) {
        int u, v; cin >> u >> v;
        G->addEdge(u - 1, v - 1);
    }
    cout << G->diameter() << '\n';
}
