// #include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 1e3 + 5;
struct Graph { 
    int V;
    struct Node : vector<Node*> {
        int dfn, low, bcc;
        bool is_cut;
        Node () { clear(); dfn = low = bcc = -1; is_cut = false; }
    }_memN[MAXN], *node[MAXN];
    Graph(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
    }
    void addEdge(int u, int v) {
        node[u]->push_back(node[v]);
        node[v]->push_back(node[u]);
    }
    
    int stamp, bcc_num, child;
    stack<Node*> stk;
    vector<Node*> BCC[MAXN];
    void findBCC() {
        stamp = bcc_num = child = 0;
        Tarjan(node[0], NULL);
    }
    void Tarjan(Node *u, Node *pa) {
        u->low = u->dfn = stamp++;
        stk.push(u);
        for (auto to : *u) {
            if (!~to->dfn) {
                Tarjan(to, u); child++;
                u->low = min(u->low, to->low);
                if (u->dfn <= to->low) {
                    u->is_cut = true;
                    BCC[bcc_num].clear();
                    Node *v;
                    do{
                        v = stk.top(); stk.pop();
                        BCC[v->bcc = bcc_num].push_back(v); 
                    }while (v != to);
                    u->bcc = bcc_num;
                    BCC[bcc_num++].push_back(u);
                }
            }else if (to->dfn < u->dfn && to != pa)
                u->low = min(u->low, to->dfn);
        }
        if (!pa && child < 2) u->is_cut = false;
    }
    int solve() {
        findBCC();
        int out_degree[MAXN]; memset(out_degree, 0, sizeof(out_degree));
        for (int _bcc = 0 ; _bcc < bcc_num ; _bcc++) {
            bool all_cut = true, inBCC[MAXN];
            memset(inBCC, false, sizeof(inBCC));
            for (auto u : BCC[_bcc]) {
                inBCC[u - _memN] = true;
                if (!u->is_cut)
                    all_cut = false;
            }
            if (all_cut) continue;
            for (auto u : BCC[_bcc]) {
                for (auto to : *u) {
                    if (inBCC[to - _memN]) continue;
                    out_degree[_bcc]++;
                }
            }
        }
        int ans = 0;
        for (int i = 0 ; i < bcc_num ; i++)
            if (out_degree[i] == 1)
                ans++;
        return (ans + 1) >> 1;
        
    }
};
int main() {
    int n, m; cin >> n >> m;
    Graph *G = new Graph(n);
    while (m--) {
        int u, v; cin >> u >> v;
        G->addEdge(u - 1, v - 1);
    }
    cout << G->solve() << '\n';
}
