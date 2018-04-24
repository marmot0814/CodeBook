// #include <bits/stdc++.h>
#include <iostream>
#include <stack>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
struct Graph{
    struct Node : vector<Node*> {
        int dfn, low, scc;
        bool in_stk;
        Node () { clear(); 
            dfn = low = scc = -1; 
            in_stk = false; 
        }
    }_memN[MAXN], *node[MAXN];
    int V;
    Graph(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
    }
    void addEdge(int u, int v){
        node[u]->push_back(node[v]);
    }
    
    int stamp, scc_num; stack<Node*> stk;
    void findSCC(){
        stamp = scc_num = 0;
        // for (auto u : node)
        for (int i = 0 ; i < V ; i++){
            Node *u = node[i];
            if (!~u->dfn)
                tarjan(u);
        }
    }
    void tarjan(Node *u) {
        u->dfn = u->low = stamp++;
        stk.push(u); u->in_stk = true;
        // for (auto to : *u){
        for (int i = 0 ; i < u->size() ; i++) {
            Node *to = u->at(i);
            if (!~to->dfn) {
                tarjan(to);
                u->low = min(u->low, to->low);
            }else if (to->in_stk)
                u->low = min(u->low, to->dfn);
        }
        if (u->dfn == u->low){
            Node *v;
            do {
                v = stk.top(); stk.pop();
                v->scc = scc_num;
                v->in_stk = false;
            }while (v != u);
            scc_num++;
        }
    }
    int solve() {
        for (int i = 0 ; i < V ; i++)
            if (!~node[i]->dfn)
                tarjan(node[i]);
        int out_degree[MAXN]; 
        memset(out_degree, 0, sizeof(out_degree));
        for (int i = 0 ; i < V ; i++) {
            // for (auto to : *node[i])
            for (int j = 0 ; j < node[i]->size() ; j++) {
                Node *to = node[i]->at(j);
                if (node[i]->scc != to->scc)
                    out_degree[node[i]->scc]++;
            }
        }
        int zero_num = 0, ansSCC = -1;
        for (int i = 0 ; i < scc_num ; i++)
            if (!out_degree[i])
                ansSCC = i, zero_num++;
        if (zero_num == 1){
            int ans = 0;
            for (int i = 0 ; i < V ; i++)
                if (node[i]->scc == ansSCC)
                    ans++;
            return ans;
        }
        return 0;
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; while (cin >> n >> m) {
        Graph *G = new Graph(n);
        while (m--) {
            int u, v; cin >> u >> v;
            G->addEdge(u - 1, v - 1);
        }
        cout << G->solve() << '\n';
    }
}
