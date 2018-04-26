#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 5;
const int lgN  = __lg(MAXN) + 5;
struct SegmentTree {
    struct Node {
        int L, R;
        Node *l, *r;
        int v;
        Node (int _L = 0, int _R = 0) {
            L = _L, R = _R;
            l = r = NULL;
        }
    }*rt, buf[lgN << 2], *ptr;
    int *arr, n;
    SegmentTree(int *_arr, int _n) {
        arr = _arr, n = _n;
        rt = build(1, n);
    }
    ~SegmentTree() { remove(rt); }
    void remove(Node *u) { if (u) remove(u->l), remove(u->r), delete u; }
    Node *build(int L, int R) {
        Node *u = new Node(L, R);
        if (R - L == 1) {
            u->v = arr[L];
            return u;
        }
        int M = (R + L) >> 1;
        u->l = build(L, M);
        u->r = build(M, R);
        return pull(u);
    }
    inline Node* pull(Node *u) {
        return pull(u, u->l, u->r);
    }
    inline Node* pull(Node *u, Node *l, Node *r) {
        if (!l || !r) return l ? l : r;
        u->v = max(l->v, r->v);
        return u;
    }
    inline void modify(int mPos, int v) {
        return modify(mPos, v, rt);
    }
    void modify(int mPos, int v, Node *u) {
        if (u->R <= mPos || mPos + 1 <= u->L) return ;
        if (mPos <= u->L && u->R <= mPos + 1) {
            u->v = v; return ;
        }
        modify(mPos, v, u->l);
        modify(mPos, v, u->r);
        pull(u);
    }
    inline Node* query(int qL, int qR) {
        ptr = buf;
        return query(qL, qR, rt);
    }
    Node* query(int qL, int qR, Node *u) {
        if (u->R <= qL || qR <= u->L) return (Node*)NULL;
        if (qL <= u->L && u->R <= qR) return u;
        return pull(ptr++, query(qL, qR, u->l), query(qL, qR, u->r));
    }
};
struct Tree {
    struct Node; struct Edge; int V;
    struct Node : vector<Edge*> {
        int sz, dep, v, dfn;
        Node *pa, *top, *hc;
    }_memN[MAXN], *node[MAXN], *rt;
    struct Edge {
        int w; Node *u, *v;
        Edge() {}
        Edge(Node *_u, Node *_v, int _w) 
            : u(_u), v(_v), w(_w) {}
    }_memE[MAXN<<1], *ptrE;
    Tree(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
        rt = node[0];
        ptrE = _memE;
    }
    inline void addEdge(int u, int v, int w) {
        node[u]->push_back(new (ptrE++) Edge(node[u], node[v], w));
        node[v]->push_back(new (ptrE++) Edge(node[v], node[u], w));
    }
    int stamp;
    inline void HLD() {
        stamp = 0; rt = node[0];
        dfs_size(rt);
        dfs_link(rt, rt);
    }
    void dfs_size(Node *u) {
        u->sz = 1, u->hc = NULL;
        for (auto e : *u) {
            Node *v = e->v;
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
        u->dfn = stamp++;
        u->top = _top;
        if (!u->hc) return ;
        dfs_link(u->hc, _top);
        for (auto e : *u) {
            Node *v = e->v;
            if (v == u->hc || v == u->pa) continue;
            dfs_link(v, v);
        }
    }
    inline bool adjust(int u, int v) {
        return node[v]->dep < node[u]->dep;
    }
    SegmentTree *seg;
    inline int query(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        Node *uTop = u->top, *vTop = v->top;
        int ans = 0;
        while (uTop != vTop) {
            if (uTop->dep < vTop->dep) 
                swap(u, v), swap(uTop, vTop);
            ans = max(ans, seg->query(uTop->dfn, u->dfn + 1)->v);
            uTop = (u = uTop->pa)->top;
        }
        if (u == v) return ans;
        if (u->dep > v->dep) swap(u, v);
        return max(ans, seg->query(u->dfn + 1, v->dfn + 1)->v);
    }
    inline void modify(int mPos, int v) {
        return seg->modify(node[mPos]->dfn, v);
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        Tree *G = new Tree(n);
        int e[MAXN][3];
        for (int i = 0 ; i < n - 1 ; i++) {
            cin >> e[i][0] >> e[i][1] >> e[i][2];
            e[i][0]--, e[i][1]--;
            G->addEdge(e[i][0], e[i][1], e[i][2]);
        }
        G->HLD();
        int arr[MAXN];
        for (int i = 0 ; i < n - 1 ; i++) {
            if (G->adjust(e[i][0], e[i][1]))
                swap(e[i][0], e[i][1]);
            arr[G->node[e[i][1]]->dfn] = e[i][2];
        }
        SegmentTree *seg = new SegmentTree(arr, n);
        G->seg = seg;
        char op[10];
        while (cin >> op) {
            if (op[0] == 'D') break;
            if (op[0] == 'C') {
                int pos, v;
                cin >> pos >> v; pos--;
                G->modify(e[pos][1], v);
            }
            if (op[0] == 'Q') {
                int u, v;
                cin >> u >> v;
                cout << G->query(u - 1, v - 1) << '\n';
            }
        }
        delete seg;
        delete G;
    }
}

