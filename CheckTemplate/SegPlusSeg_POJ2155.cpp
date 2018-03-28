#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 5;
const int lgN = __lg(MAXN) + 5;
template <typename T>
class SegmemtTree{
	private:
	struct Node{
		int L, R;
		Node *l, *r;
		T v;
		bool rev;
		Node (int _L = 0, int _R = 0){
			L = _L, R = _R;
			l = r = NULL;
		}
		int len() { return R - L; }
		int mid() { return (R + L) >> 1; }
	}*rt, buf[15], *ptr;
	int n;
	void init(SegmentTree<bool> *&ST){
		ST = new SegmentTree<bool>(ST->L, ST->R);
	}
	void init(bool& v){
		v = false;
	}
	Node* build(int L, int R){
		Node *u = new Node(L, R);
		if (u->len() == 1){
			init(u->v);
			return u;
		}
		int M = u->mid();
		u->l = build(L, M);
		u->r = build(M, R);
		return pull(u);
	}
	Node *pull(Node *u){
		return pull(u, u->l, u->r);
	}
	Node* pull(Node *u, Node *l, Node *r){
		if (!l || !r) return l ? l : r;
		push(l), push(r);
		u->sum = l->sum + r->sum;
		return u;
	}
	void push(Node *u){
		if (!u) return ;
		if (u->rev){
			reverse(u->v);
			if (u->l) u->l->rev ^= 1;
			if (u->r) u->r->rev ^= 1;
			u->rev = false;
		}
	}
	void reverse(SegmentTree &ST){
		ST->rt->rev ^= 1;
	}
	void reverse(bool &v){
		v ^= 1;
	}
	void modify(int mL, int mR, Node *u){
		if (u->R <= mL || mR <= u->L) return ;
		if (mL <= u->L && u->R <= mR){
			u->rev ^= 1;
			return ;
		}
		push(u);
		int M = u->mid();
		modify(mL, mR, u->l);
		modify(mL, mR, u->r);
		pull(u);
	}
	Node* query(int qL, int qR, Node *u){
		if (u->R <= qL || qR <= u->L) return (Node*)NULL;
		if (qL <= u->L && u->R <= qR) return u;
		push(u);
		return pull(ptr++, query(qL, qR, u->l), query(qL, qR, u->r));
	}
	public:
	SegmentTree(int _n){
		n = _n; ptr = buf;
		rt = build(0, n);
	}
	Node* query(int qL, int qR){
		ptr = buf;
		return query(qL, qR, rt);
	}
	void modify(int mL, int mR){
		modify(mL, mR, rt);
	}
};
int main(){
	//SegmentTree<SegmentTree<bool>* > *sol = new SegmentTree<SegmentTree<bool>* > (range)
}
