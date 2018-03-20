#include <bits/stdc++.h>
using namespace std;
const int MAXN  = 1000 + 5;
const int lgN = __lg(MAXN) + 5;
typedef long long LL;
struct SegmentTree{
	struct Node{
		int L, R;
		Node *l ,*r;
		// data
		LL sum, maxV, minV;
		// tag
		bool isChg;
		LL add, chg;

		int len() { return R - L; }
		int mid() { return (R + L) >> 1; }
	}_mem[MAXN<<1], *ptr, ans[lgN], *buf;
	SegmentTree(LL *arr, int n){
		ptr = _mem, buf = ans;
		build(arr, 0, n, ptr++);
	}
	void build(LL *arr, int L, int R, Node *u){
		u->L = L, u->R = R;
		if (u->len() == 1) {
			// base data
			u->sum = u->maxV = u->minV = arr[L];
			u->add = u->chg = 0;
			u->isChg = false;
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
		// pull function
		push(l), push(r);
		u->sum = l->sum + r->sum;
		u->maxV = max(l->maxV, r->maxV);
		u->minV = min(l->minV, r->minV);
		return u;
	}
	void push(Node *u){
		if (!u) return;
		// push function
		if (u->isChg){
			u->isChg = false;
			u->maxV = u->minV = u->chg;
			u->sum = u->len() * u->chg;
			if (Node *t = u->l){
				t->add = 0;
				t->isChg = true;
				t->chg = u->chg;
			}
			if (Node *t = u->r){
				t->add = 0;
				t->isChg = true;
				t->chg = u->chg;
			}
			u->chg = 0;
		}
		if (u->add){
			u->maxV += u->add;
			u->minV += u->add;
			u->sum += u->len() * u->add;
			if (Node *t = u->l){
				t->add += u->add;
			}
			if (Node *t = u->r){
				t->add += u->add;
			}
			u->add = 0;
		}	
	}
	void addValue(int L, int R, int v, Node *u = NULL){
		if (!u) u = _mem;
		push(u);
		if (L <= u->L && u->R <= R){
			u->add += v;
			// tag
		}else if (L < u->R && u->L < R){
			int M = u->mid();
			addValue(L, R, v, u->l);
			addValue(L, R, v, u->r);
			pull(u);
		}else return ;
	}
	void chgValue(int L, int R, int v, Node *u = NULL){
		if (!u) u = _mem;
		push(u);
		if (L <= u->L && u->R <= R){
			// tag
			u->isChg = true;
			u->add = 0;
			u->chg = v;
		}else if (L < u->R && u->L < R){
			int M = u->mid();
			chgValue(L, R, v, u->l);
			chgValue(L, R, v, u->r);
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
	void Print(Node *u = NULL){
		if (!u) {
			u = _mem;
			cout << "L\tR\tsum\tmaxV\tminV\tadd\tisChg\tchg\n";
		}
		cout << u->L << '\t' << u->R << '\t' << u->sum << '\t' << u->maxV << '\t' << u->minV << '\t' << u->add << '\t' << u->isChg << '\t' << u->chg << '\n';
		if (u->l) Print(u->l);
		if (u->r) Print(u->r);
	}
};
int main(){
	int n, q;
	cin >> n >> q;
	LL data[MAXN];
	for (int i = 0 ; i < n ; i++) cin >> data[i];
	SegmentTree *sol = new SegmentTree(data, n);
	char buf[10];
	while (q--){
		cin >> buf;
		LL a, b, v = 0;
		switch(buf[1]){
			case 'd':
				cin >> a >> b >> v;
				a--;
				sol->addValue(a, b, v);
				break;
			case 'e':
				cin >> a >> b >> v;
				a--;
				sol->chgValue(a, b, v);
				break;
			case 'u':
				cin >> a >> b;
				a--;
				cout << sol->query(a, b)->sum << '\n';
				break;
			case 'a':
				cin >> a >> b;
				a--;
				cout << sol->query(a, b)->maxV << '\n';
				break;
			case 'i':
				cin >> a >> b;
				a--;
				cout << sol->query(a, b)->minV << '\n';
				break;
		}
	}
	delete sol;
}
