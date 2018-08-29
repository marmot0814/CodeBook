#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
const int MAXN = 4e4 + 5;
const int MAXQ = 1e5 + 5;
const int lgN  = __lg(MAXN) + 5;
typedef pair<int, int> pii;
struct Tree { int n, stamp, stampMapId[MAXN * 2];
    struct Node : vector<Node*> {
        int w, dep, in, out;
        Node *pa[lgN];
        Node(int _w = 0) : w(_w), dep(-1) {
            memset(pa, 0, sizeof(pa));
            in = out = -1; 
        }
    }_memN[MAXN], *node[MAXN];
    inline int getId(Node *u) { return u - _memN; }
    Tree(int _n) : n(_n) {
        for (int i = 0 ; i < n ; i++)
            node[i] = _memN + i;
        memset(stampMapId, -1, sizeof(stampMapId));
        stamp = 0;
    }
    void addEdge(int u, int v) {
        node[u]->push_back(node[v]);
        node[v]->push_back(node[u]);
    }
    void dfs(Node *u, Node *pa, int dep) {
        u->in = stamp++;
        u->pa[0] = pa; u->dep = dep;
        for (int i = 1 ; i < lgN ; i++)
            u->pa[i] = u->pa[i - 1]->pa[i - 1];
        for (auto v : *u) {
            if (!~v->dep)
                dfs(v, u, dep + 1);
        }
        u->out = stamp++; 
        stampMapId[u->in ] = getId(u);
        stampMapId[u->out] = getId(u);
    }
    void buildLCA() {
        dfs(node[0], node[0], 0);
    }
    Node* LCA(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        if (u->dep < v->dep) swap(u, v);
        for (int i = lgN - 1 ; ~i ; i--) 
            if (u->pa[i]->dep >= v->dep)
                u = u->pa[i];
        if (u == v) return u;
        for (int i = lgN - 1 ; ~i ; i--) 
            if (u->pa[i] != v->pa[i])
                u = u->pa[i], v = v->pa[i];
        return u->pa[0];
    }
    pii flatenTree(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        if (v->in < u->in) swap(u, v);
        Node *lca = LCA(_u, _v);
        pii ret = make_pair((lca == u ? u->in : u->out), v->in + 1);
        return ret;
    }
};
struct MO {
    struct Q {
        int l, r, id, b;
        Q(int _l, int _r, int _id, int _b) 
            : l(_l), r(_r), id(_id), b(_b) {}
        bool operator < (const Q &q) const {
            return b == q.b ? r < q.r : l < q.l;
        }
    };
    int qn, sqn;
    Tree *T; vector<Q> qs;
    bool inSeg[MAXN];
    int cnt[MAXN], sz;
    MO(Tree *_T, vector<pii> &_qs) : T(_T) {
        memset(cnt, 0, sizeof(cnt)); sz = 0;
        T->buildLCA(); qn = _qs.size(), sqn = (int)(sqrt(qn) + 1e-6);
        for (int i = 0 ; i < qn ; i++) {
            pii q = T->flatenTree(_qs[i].F, _qs[i].S);
            qs.emplace_back(q.F, q.S, i, q.F / sqn);
        }
    }
    vector<int> solve() {
        vector<int> ret(qn);
        int *stampMapId = T->stampMapId;
        sort(qs.begin(), qs.end());
        memset(inSeg, false, sizeof(inSeg));
        int l = 0, r = 0;
        for (auto q : qs) {
            while (r < q.r) update(stampMapId[r]), r++;
            while (r > q.r) --r, update(stampMapId[r]);
            while (l > q.l) --l, update(stampMapId[l]);
            while (l < q.l) update(stampMapId[l]), l++;
            auto lca = T->LCA(stampMapId[l], stampMapId[r - 1]);
            ret[q.id] = sz + (cnt[lca->w] == 0);
        }
        return ret;
    }
    void update(int num) {
        int w = T->node[num]->w;
        if (inSeg[num]){
            cnt[w]--;
            if (!cnt[w]) sz--;
        } else { 
            if (!cnt[w]) sz++;
            cnt[w]++;
        }
        inSeg[num] ^= 1;
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; while (cin >> n >> q) {
        Tree *T = new Tree(n);
        vector<int> ws;
        for (int i = 0 ; i < n ; i++) {
            int input; cin >> input;
            ws.push_back(input);
        }
        vector<int> f = ws;
        sort(f.begin(), f.end());
        f.erase(unique(f.begin(), f.end()), f.end());
        for (int i = 0 ; i < n ; i++) 
            T->node[i]->w = lower_bound(f.begin(), f.end(), ws[i]) - f.begin();
        for (int i = 0 ; i < n - 1 ; i++) {
            int u, v; cin >> u >> v; u--, v--;
            T->addEdge(u, v);
        }
        vector<pii> qs(q);
        for (auto &q : qs) { 
            cin >> q.F >> q.S;
            q.F--; q.S--;
        }
        MO *sol = new MO(T, qs);
        vector<int> ans = sol->solve();
        for (auto num : ans)
            cout << num << '\n';
        delete sol;
        delete T;
    }
}

