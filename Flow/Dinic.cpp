#include <bits/stdc++.h>
using namespace std;
#define PB push_back
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e3 + 5;
const int MAXM = (MAXN * MAXN) / 2;
struct Graph{
    struct Node; struct Edge;
    int V;
    struct Node : vector<Edge*>{
        iterator cur; int d;
        Node(){ clear(); }
    }_memN[MAXN], *node[MAXN];
    struct Edge{
        Node *u, *v; 
        Edge *rev;
        LL c, f;
        Edge(){}
        Edge(Node *u, Node *v, LL c, Edge *rev) : u(u), v(v), c(c), f(0), rev(rev){}
    }_memE[MAXM], *ptrE;
    Graph(int _V){
        for (int i = 0 ; i < (V = _V) ; i++)
            *(node[i] = _memN + i) = Node();
        ptrE = _memE;
    }
    void addEdge(int _u, int _v, LL _c){
        *ptrE = Edge(node[_u], node[_v], _c, ptrE + 1);
        node[_u]->PB(ptrE++);
        *ptrE = Edge(node[_v], node[_u], _c, ptrE - 1);
        node[_v]->PB(ptrE++);
    }
};
typedef Graph::Node Node;
#define qpush(s, n) q.push(s), s->d = n
#define qpop() q.front(); q.pop()
struct Dinic{
    Graph *G;
    Node **node, *s, *t;
    Dinic(Graph *_G, int _s, int _t){
        G = _G, node = &G->node[0];
        s = node[_s], t = node[_t];
    }
    bool bfs(){
        for (int i = 0 ; i < G->V ; i++) node[i]->d = -1;
        queue<Node*> q; qpush(s, 0);
        while (q.size()){
            Node *u = qpop();
            for (auto e : *u){
                Node *v = e->v;
                if (!~v->d && e->c > e->f)
                    qpush(v, u->d + 1);
            }
        }
        return ~t->d;
    }
    LL dfs(Node *u, LL a){
        if (u == t || !a) return a;
        LL flow = 0, f;
        for (; u->cur != u->end() ; u->cur++){
            auto &e = *u->cur; Node *v = e->v;
            if (u->d + 1 == v->d && (f = dfs(v, min(a, e->c - e->f))) > 0){
                e->f += f; e->rev->f -= f;
                flow += f; a -= f;
                if (!a) break;
            }
        }
        return flow;
    }
    LL maxFlow(){
        LL flow = 0;
        while (bfs()){
            for (int i = 0 ; i < G->V ; i++)
                node[i]->cur = node[i]->begin();
            flow += dfs(s, INF);
        }
        return flow;
    }
};
int main(){
}
