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
        for (auto u : node)
            if (!~u->dfn)
                tarjan(u);
    }
    void tarjan(Node *u) {
        u->dfn = u->low = stamp++;
        stk.push(u); u->in_stk = true;
        for (auto to : *u){
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
}
int main() { 

}
