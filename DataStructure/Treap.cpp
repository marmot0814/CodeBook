#include <bits/stdc++.h>
using namespace std;
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
		inline int size(){
			return this ? sz : 0;
		}
		inline void pull(){
			sz = 1 + l->size() + r->size();
		}	
		inline void push(){

		}
	}*root;
#define PNN pair<Node*, Node*>
#define MP make_pair
#define F first
#define S second
	PNN split(Node *T, int x){
		if (!T) return MP((Node*)NULL, (Node*)NULL);
		T->push();
		if (T->l->size() < x){
			PNN tmp = split(T->r, x - T->l->size() - 1);
			T->r =tmp.F;
			T->pull();
			return MP(T, tmp.S);
		}else{
			PNN tmp = split(T->l, x);
			T->l = tmp.S;
			T->pull();
			return MP(tmp.F, T);
		}
	}
	Node* merge(Node *T1, Node *T2){
		if (!T1 || !T2) return T1 ? T1 : T2;
		if (T1->pri < T2->pri){
			T2->push();
			T2->l = merge(T1, T2->l);
			T2->pull();
			return T2;
		}else{
			T1->push();
			T1->r = merge(T1->r, T2);
			T1->pull();
			return T1;
		}
	}
	int rank(int v, Node *u = NULL, bool first = true){
		if (first) u = root;
		if (!u) return 0;
		if (v < u->v)
			return rank(v, u->l, false);
		else
			return u->l->size() + rank(v, u->r, false) + 1;
	}
	void insert(int v, int k = -1){
		if (!~k) k = rank(v);
		PNN tmp = split(root, k);
		root = merge(merge(tmp.F, new Node(v)), tmp.S);
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
