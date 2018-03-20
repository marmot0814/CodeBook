#include <bits/stdc++.h>
using namespace std;
const int MAXN  = 1000 + 5;
const int lgN = __lg(MAXN) + 5;
struct SegmentTree{
	struct Node{
		int L, R;
		Node *l ,*r;
		// data
		// tag
		int len() { return R - L; }
		int mid() { return (R + L) >> 1; }
	}_mem[MAXN<<1], *ptr, ans[lgN], *buf;
	SegmentTree(int *arr, int n){
		ptr = _mem, buf = ans;
		build(arr, 0, n, ptr++);
	}
	void build(int *arr, int L, int R, Node *u){
		u->L = L, u->R = R;
		if (u->len() == 1) {
			// base data
			return ;
		}
		int M = u->mid();
		build(arr, L, M, u->l = ptr++);
		build(arr, M, R, u->r = ptr++);
		pull(u);
	}
	Node* pull(Node *u, Node *l = NULL, Node *r = NULL){
		if (!l) l = u->l;
		if (!r) r = u->r;
		push(l); push(r);
		// pull function
		return u;
	}
	void push(Node *u){
		if (!u) return ;
		// push function
	}
	void modify(int L, int R, int v, Node *u = NULL){
		if (!u) u = _mem;
		push(u);
		if (L <= u->L && u->R <= R){
			// tag
		}else if (L < u->R && u->L < R){
			int M = u->mid();
			modify(L, R, v, u->l);
			modify(L, R, v, u->r);
			pull(u);
		}else return ;
	}
	Node* query(int L, int R, Node *u = NULL){
		if (!u) u = _mem, buf = ans;
		push(u);
		if (L <= u->L && u->R <= R) return u;
		int M = u->mid();
		if (R <= M) return query(L, R, u->l);
		else if (L >= M) return query(L, R, u->r);
		else return pull(buf++, query(L, R, u->l), query(L, R, u->r));
	}

};
int main(){

}
