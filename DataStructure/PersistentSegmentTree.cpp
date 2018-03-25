#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e4 + 5;;
const int lgN = __lg(MAXN) + 5;
const int MAXK = 100;
struct SegmentTree{
	struct Node{
		int L, R;
		Node *l, *r;
		// data
		Node(int _L = 0, int _R = 0){
			L = _L, R = _R;
			l = r = NULL;
		}
		int len(){ return R - L; }
		int mid(){ return (R + L) >> 1; }
	}*rt[MAXK], buf[lgN<<2], *ptr;
	int *arr, n;
	SegmentTree(int *_arr, int _n){
		arr = _arr, n = _n;
		ptr = buf;
		rt[0] = build(0, n);
	}
	~SegmentTree(){
		remove(rt);
	}
	void remove(Node *u){
		if (!u)  return;
		remove(u->l), remove(u->r);
		delete u;
	}
	Node* build(int L, int R){
		Node *u = new Node(L, R);
		if (u->len() == 1) {
			// base data
			return u;
		}
		int M = u->mid();
		u->l = build(L, M);
		u->r = build(M, R);
		return pull(u);
	}
	Node* pull(Node *u, bool single = true, Node *l = NULL, Node *r = NULL){
		if (single) l = u->l, r = u->r;
		if (!l || !r) return l ? l : r;
		push(l), push(r);
		// pull function
		return u;
	}
	void push(Node *u){
		if (!u) return ;
		// push function
	}
	void modify(int mL, int mR, int v, Node *u = NULL){
		if (!u) u = rt;
		if (u->R <= mL || mR <= u->L) return ;
		if (mL <= u->L && u->R <= mR){
			// tag
			return ;
		}
		push(u);
		int M = u->mid();
		modify(mL, mR, v, u->l);
		modify(mL, mR, v, u->r);
		pull(u);
	}
	Node* query(int qL, int qR, Node *u = NULL){
		if (!u) u = rt, ptr = buf;
		if (u->R <= qL || qR <= u->L) return (Node*)NULL;
		if (qL <= u->L && u->R <= qR) return u;
		push(u);
		return pull(ptr++, false, query(qL, qR, u->l), query(qL, qR, u->r));
	}
};
int main(){
}
