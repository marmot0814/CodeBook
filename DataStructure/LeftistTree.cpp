#include <bits/stdc++.h>
using namespace std;
struct LeftistTree{
    struct Node{
        int v, d;
        Node *l, *r;
        Node(int _v = 0) : v(_v), d(1), l(NULL), r(NULL){}
        inline int deep(){ return this ? d : 0; }
        inline void pull(){
            if (l->deep() < r->deep()) swap(l, r);
            d = 1 + r->deep();
        }
    }*rt;
    int sz;
    LeftistTree(){ sz = 0; rt = NULL; }
    ~LeftistTree(){ remove(rt); }
    Node* merge(Node *L1, Node *L2){
        if (!L1 || !L2) return L1 ? L1 : L2;
        if (L1->v < L2->v){
            L1->r = merge(L1->r, L2);
            L1->pull();
            return L1;
        }else{
            L2->r = merge(L2->r, L1);
            L2->pull();
            return L2;
        }
    }
    void push(int v){
        rt = merge(rt, new Node(v)); sz++;
    }
    void pop(){
        Node *tmp = rt;
        rt = merge(rt->l, rt->r);
        delete tmp;
        sz--;
    }
    void join(LeftistTree *L){
        rt = merge(rt, L->rt);
        L->rt = NULL;
        sz += L->sz;
        L->sz = 0;
    }
    int size(){  return sz; }
    int top(){ return rt->v; }
    bool empty(){ return !sz; }
    void remove(Node *u){ 
        if (!u) return ;
        remove(u->l);
        remove(u->r); 
        delete u; 
    }
};
int main(){

}
