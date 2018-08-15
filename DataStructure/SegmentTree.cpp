#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1e4 + 5;
const int lgN = __lg(MAXN) + 5;
struct SegmentTree {
    struct Node {
        int L, R; 
        Node *l, *r;
        // data
        // tag
        Node (int _L = 0,int _R = 0) : L(_L), R(_R) {
            l = r = NULL;
        }
    }*rt, buf[lgN << 2], *ptr;
    LL *arr; int n;
    SegmentTree(LL *_arr, int _n) {
        arr = _arr, n = _n;
        rt = build(0, n);
    }

    ~SegmentTree() {
        remove(rt);
    }
    void remove(Node *u) {
        if (!u) return ;
        remove(u->r);
        remove(u->l);
        delete u;
    }
    Node* build(int L, int R) {
        Node *u = new Node(L, R);
        if (R - L == 1) {
            // basic data
            return u;
        }
        int M = (R + L) >> 1;
        u->l = build(L, M);
        u->r = build(M, R);
        return pull(u);
    }
    Node* pull(Node *u) {
        return pull(u, u->l, u->r);
    }
    Node* pull(Node *u, Node *l, Node *r) {
        if (!l || !r) return l ? l : r;
        push(l); push(r);
        // pull function;
        return u;
    }
    void push(Node *u) {
        if (!u) return ;
        // push function
    }
    Node* query(int qL, int qR) {
        ptr = buf;
        return query(qL, qR, rt);
    }
    Node* query(int qL, int qR, Node *u) {
        if (u->R <= qL || qR <= u->L) return (Node*)NULL;
        if (qL <= u->L && u->R <= qR) return u;
        push(u);
        return pull(ptr++, query(qL, qR, u->l), query(qL, qR, u->r));
    }
    void modify(int mL, int mR) {
        return modify(mL, mR, rt);
    }
    void modify(int mL, int mR, Node *u) {
        if (u->R <= mL || mR <= u->L) return ;
        if (mL <= u->L && u->R <= mR) {
            // modify function
            return ;
        }
        push(u);
        modify(mL, mR, u->l);
        modify(mL, mR, u->r);
        pull(u);
    }
};
int main() {

}
