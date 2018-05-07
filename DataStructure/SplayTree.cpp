#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
struct SplayTree {
    struct Node {
        Node *ch[2], *pa;
        int v, sz;
        Node (int _v, Node *_pa) : v(_v), pa(_pa) { 
            ch[0] = ch[1] = NULL; sz = 1;
        }
    }*rt;
    SplayTree() {
        rt = new Node(INF, NULL);
        rt->ch[1] = new Node(INF, rt);
        pull(rt);
    }
    inline int size(Node *u) {
        return u ? u->sz : 0;
    }
    inline void pull(Node *u) {
        u->sz = 1 + size(u->ch[0]) + size(u->ch[1]);
    }
    void splay(Node *u, Node *t) {
        while (u->pa != t) {
            Node *p = u->pa;
            if (p->pa == t) {
                rotate(u, u == p->ch[0]);
                break;
            }
            bool x = u != p->ch[0], y = p == p->pa->ch[x];
            rotate(y ? p : u, !x); rotate(u, x ^ y);
        }
        if (t == NULL) rt = u;
    }
    void rotate(Node *u, bool T) {
        Node *p = u->pa; p->ch[T^1] = u->ch[T];
        if (u->ch[T]) u->ch[T]->pa = p;
        u->pa = p->pa; u->ch[T] = p;
        if (p->pa) p->pa->ch[p != p->pa->ch[0]] = u;
        p->pa = u; pull(p); pull(u);
    }
    Node* find_kth(int k, Node *u = NULL) {
        if (!u) u = rt;
        if (size(u->ch[0]) == k) return u;
        if (size(u->ch[0]) < k) return find_kth(k - size(u->ch[0]) - 1, u->ch[1]);
        else return find_kth(k, u->ch[0]);
    }
    void insert(int v, int k) {
        splay(find_kth(k), NULL);
        splay(find_kth(k + 1), rt);
        rt->ch[1]->ch[0] = new Node(v, rt->ch[1]);
        splay(rt->ch[1]->ch[0], rt);
    }
    void query(int l, int r) {
        splay(find_kth(l), NULL);
        splay(find_kth(r + 1), rt);
        /* [l, r) */
    }
};
int main() {
    SplayTree *sol = new SplayTree();
    int n = 10;
    for (int i = 0 ; i < n ; i++) {
        int tmp = rand() % 20;
        cout << tmp << ' ';
        sol->insert(tmp, i);
    }
    cout << '\n';
    int l, r; while (cin >> l >> r) {
        sol->query(l, r); 
    }
    delete sol;
}

