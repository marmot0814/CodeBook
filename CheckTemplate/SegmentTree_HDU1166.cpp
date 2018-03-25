#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e4 + 5;;
const int lgN = __lg(MAXN) + 5;
const int MAXK = 100;
struct SegmentTree{
	struct Node{
		int L, R;
		Node *l, *r;
		int sum;
		int add;
		Node(int _L = 0, int _R = 0){
			L = _L, R = _R;
			sum = 0, add = 0;
			l = r = NULL;
		}
		int len(){ return R - L; }
		int mid(){ return (R + L) >> 1; }
	}*rt, buf[lgN<<2], *ptr;
	int *arr, n;
	SegmentTree(int *_arr, int _n){
		arr = _arr, n = _n;
		ptr = buf;
		rt = build(0, n);
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
			u->sum = arr[L];
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
		u->sum = l->sum + r->sum;
		return u;
	}
	void push(Node *u){
		if (!u) return ;
		if (u->add){
			u->sum += u->add * u->len();
			if (u->l) u->l->add += u->add;
			if (u->r) u->r->add += u->add;
			u->add = 0;
		}
	}
	void modify(int mL, int mR, int v, Node *u = NULL){
		if (!u) u = rt;
		if (u->R <= mL || mR <= u->L) return ;
		if (mL <= u->L && u->R <= mR){
			u->add += v;
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
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t, kase = 0; cin >> t; while (t--){
		cout << "Case " << ++kase << ":\n";
		int n, arr[MAXN]; cin >> n;
		for (int i = 0 ; i < n ; i++) cin >> arr[i];
		SegmentTree *sol = new SegmentTree(arr, n);
		char op[8];
		while (cin >> op){
			if (op[0] == 'E') break;
			int a, b, v;
			if (op[0] == 'A'){
				cin >> a >> v;
				sol->modify(a-1, a, v);
			}
			if (op[0] == 'S'){
				cin >> a >> v;
				sol->modify(a-1, a, -v);
			}
			if (op[0] == 'Q'){
				cin >> a >> b;
				cout << sol->query(a-1, b)->sum << '\n';
			}
		}
		delete sol;
	}
}
