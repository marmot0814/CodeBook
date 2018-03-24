#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
struct Treap{
	struct Node{
		Node *l, *r;
		int v, pri, sz;
		Node (int _v = 0){
			v = _v;
			pri = rand();
			sz = 1;
			l = r = NULL;
		}
	}*root, _mem[MAXN], *ptr;
	Treap(){
		ptr = _mem;
	}
	inline int size(Node *u){
		return u ? u->sz : 0;
	}
	inline void pull(Node *u){
		u->sz = 1 + size(u->l) + size(u->r);

	}
	inline void push(Node *u){

	}
#define PNN pair<Node*, Node*>
#define MP make_pair
#define F first
#define S second
	PNN split(Node *T, int x){
		if (!T) return MP((Node*)NULL, (Node*)NULL);
		push(T);
		if (size(T->l) < x){
			PNN tmp = split(T->r, x - size(T->l) - 1);
			T->r =tmp.F;
			pull(T);
			return MP(T, tmp.S);
		}else{
			PNN tmp = split(T->l, x);
			T->l = tmp.S;
			pull(T);
			return MP(tmp.F, T);
		}
	}
	Node* merge(Node *T1, Node *T2){
		if (!T1 || !T2) return T1 ? T1 : T2;
		if (T1->pri < T2->pri){
			push(T2);
			T2->l = merge(T1, T2->l);
			pull(T2);
			return T2;
		}else{
			push(T1);
			T1->r = merge(T1->r, T2);
			pull(T1);
			return T1;
		}
	}
	int rank(int v, Node *u = NULL, bool first = true){
		if (first) u = root;
		if (!u) return 0;
		if (v < u->v)
			return rank(v, u->l, false);
		else
			return size(u->l) + rank(v, u->r, false) + 1;
	}
	void insert(int v, int k = -1){
		if (!~k) k = rank(v);
		PNN tmp = split(root, k);
		root = merge(merge(tmp.F, new (ptr++) Node(v)), tmp.S);
	}
	void Print(Node *u = NULL){
		if (!u) u = root;
		if (u->l) Print(u->l);
		cout << u->v << ' ';
		if (u->r) Print(u->r);
		if (u == root) cout << '\n';
	}
};
int main(){
	Treap *sol = new Treap();
	int n; cin >> n;
	for (int i = 0 ; i < n ; i++){
		int tmp; cin >> tmp;
		sol->insert(tmp);
		sol->Print();
	}
	delete sol;
}
