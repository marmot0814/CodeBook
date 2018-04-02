#include <bits/stdc++.h>
using namespace std;
#define PB push_back
typedef long long LL;
const int MAXN = 300;
const int MAXM = MAXN * MAXN;
const LL INF = 0x3f3f3f3f3f3f3f3f;
struct Graph{
    struct Node; struct Edge;
    int V;
    struct Node : vector<Edge*>{
        bool inq;
        LL a, d;
        Edge *p;
        Node(){clear();}
    }_memN[MAXN], *node[MAXN];
    struct Edge{
        Node *u, *v;
        Edge *rev;
        LL c, f, _c;
        Edge(){}
        Edge(Node* u, Node* v, LL c, LL _c, Edge* rev) : u(u), v(v), c(c), _c(_c), f(0), rev(rev){}
    }_memE[MAXM], *ptrE;
    Graph(int _V = 0) : V(_V){
        for (int i = 0 ; i < V ; i++)
            *(node[i] = _memN + i) = Node();
        ptrE = _memE;
    }
    void addEdge(int u, int v, LL c, LL _c){
        node[u]->PB(new (ptrE++) Edge(node[u], node[v], c, _c, ptrE + 1));
        node[v]->PB(new (ptrE++) Edge(node[v], node[u], 0, -_c, ptrE - 1));
    }
};
typedef Graph::Node Node;
struct MCMF{
    Graph *G;
    Node *s, *t, **node;
    MCMF(Graph *G, int _s, int _t) : G(G){
        node = &G->node[0];
        s = node[_s], t = node[_t];
    }
    LL maxFlowMinCut(LL& cost){
        LL flow = 0;
        cost = 0;
        while (SPFA(s, t, flow, cost));
        return flow;
    }
#define qpush(s) q.push(s), s->inq = true
#define qpop() q.front(); q.pop(); p->inq = false
    bool SPFA(Node *s, Node *t, LL &flow, LL &cost){
        for (int i = 0 ; i < G->V ; i++){
            node[i]->d = INF;
            node[i]->inq = false;
        }
        s->d = 0, s->a = INF; s->p = NULL;
        queue<Node*> q; qpush(s);
        while (q.size()){
            Node *p = qpop();
            for (auto &e : *p){
                if (e->c > e->f && e->v->d > p->d + e->_c){
                    e->v->d = p->d + e->_c;
                    e->v->p = e;
                    e->v->a= min(p->a, e->c - e->f);
                    if (!e->v->inq) qpush(e->v);
                }
            }
        }
        if (t->d == INF) return false;
        flow += t->a; cost += t->d * t->a;
        for (auto u = t ; u != s ; u = u->p->u){
            u->p->f += t->a;
            u->p->rev->f -= t->a;
        }
        return true;
    }
};
int main(){

}
