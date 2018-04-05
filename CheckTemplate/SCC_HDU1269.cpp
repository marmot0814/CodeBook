#include <bits/stdc++.h>
using namespace std;
#define PB push_back
const int MAXN = 1e4 + 5;
const int MAXM = 1e5 + 5;
struct Graph{
    struct Node; struct Edge; int V;
    struct Node : vector<Edge*> {
        bool v; int scc;
        Node () { clear(), v = false, scc = -1; }
    }_memN[MAXN << 1], *node[MAXN << 1];
    struct Edge{
        Node *v;
        Edge(Node *v = NULL) : v(v) {}
    }_memE[MAXM << 1], *ptrE;
    Graph(int V) : V(V){
        for (int i = 0 ; i < V * 2 ; i++)
            *(node[i] = _memN + i) = Node();
        ptrE = _memE;
    }
    void addEdge(int u, int v){
        node[u]->PB(new (ptrE++) Edge(node[v]));
        node[v + V]->PB(new (ptrE++) Edge(node[u]));
    }
};
typedef Graph::Node Node;
struct SCC{
    Graph *G; Node **node; int sccNum;
    stack<Node*> s;
    SCC(Graph *G) : G(G) {
        node = &G->node[0];
        sccNum = findSCC();
    }
    void dfs(Node *u){
        u->v = true;
        for (auto &e : *u)
            if (!e->v->v)
                dfs(e->v);
        s.push(u);
    }
    void dfs2(Node *u, int k){
        if (~u->scc) return ;
        u->scc = k;
        for (auto &e : *(u + G->V))
            dfs2(e->v, k);
    }
    int findSCC(){
        for (int i = 0 ; i < G->V ; i++) 
            if (!node[i]->v) dfs(node[i]);
        int t = 0;
        while (s.size()){
            if (!~s.top()->scc)
                dfs2(s.top(), t++);
            s.pop();
        }
        return t;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m; while (cin >> n >> m && (n || m) ){
        Graph *G = new Graph(n);
        while (m--){
            int a, b; cin >> a >> b;
            G->addEdge(a - 1, b - 1);
        }
        SCC *sol = new SCC(G);
        if (sol->sccNum == 1) cout << "Yes\n";
        else cout << "No\n";
    }
}
