#include <bits/stdc++.h>
using namespace std;
#define PB push_back
const int MAXN = 1000;
const int MAXM = 1000;
typedef long long LL;
struct Graph{
    struct Node; struct Edge; int V;
    struct Node : vector<Edge*> {
        bool inq; int cnt; LL d;
        Node() { clear(), inq = cnt = 0; }
    }_memN[MAXN], *node[MAXN];
    struct Edge{
        Node *v; LL w;
        Edge(Node *v = NULL, LL w = 0) : v(v), w(w) {}
    }_memE[MAXM], *ptrE;
    Graph(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            *(node[i] = _memN + i) = Node();
        ptrE = _memE;
    }
    void addEdge(int u, int v, LL w){
        node[u]->PB(new (ptrE++) Edge(node[v], w));
        node[v]->PB(new (ptrE++) Edge(node[u], w));
    }
};
typedef Graph::Node Node;
void SPFA(Graph *G, int _s){
    Node **node = &G->node[0], *s = node[_s];
    s->d = 0, s->inq = true; 
    queue<Node*> q; q.push(node[_s]);
    while (q.size()){
        Node *p = q.front(); q.pop(); p->inq = false;
        p->cnt++; if (p->cnt > G->V) { s->d = -1; break; }
        for (auto &e : *p){
            if (p->d + e->w < e->v->d){
                e->v->d = p->d + e->w;
                if (!e->v->inq)
                    e->v->inq = true, q.push(e->v);
            }
        }
    }
}
int main(){

}
