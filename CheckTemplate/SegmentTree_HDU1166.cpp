#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e4 + 5;
const int lgN = __lg(MAXN) + 5;
struct SegmentTree{
	struct Node{
		int L, R;
		Node *l ,*r;
		int sum;
		int len() { return R - L; }
		int mid() { return (R + L) >> 1; }
	}_mem[MAXN<<1], *ptr, buf[lgN], *ans;
	SegmentTree(int *arr, int n){
		ptr =  _mem, ans = buf;
		build(arr, 0, n, ptr++);
	}
	void build(int* arr, int L, int R, Node *u){
		u->L = L, u->R = R;
		if (u->len() == 1){
			u->sum = arr[L];
			return ;
		}
		int M = u->mid();
		build(arr, L, M, u->l = ptr++);
		build(arr, M, R, u->r = ptr++);
		pull(u);
	}
	Node *pull(Node *u, Node *l = NULL, Node *r = NULL){
		if (!l) l = u->l;
		if (!r) r = u->r;
		u->sum = l->sum + r->sum;
		return u;
	}
	void modify(int L, int R, int v, Node *u = NULL){
		if (!u) u = _mem;
		if (L <= u->L && u->R <= R){
			u->sum += v;
		}else if (L < u->R && u->L < R){
			int M = u->mid();
			modify(L, R, v, u->l);
			modify(L, R, v, u->r);
			pull(u);
		}else return ;
	}
	Node* query(int L, int R, Node *u = NULL){
		if (!u) u = _mem, ans = buf;
		if (L <= u->L && u->R <= R) return u;
		int M = u->mid();
		if (R <= M) return query(L, R, u->l);
		else if (L >= M) return query(L, R, u->r);
		else return pull(ans++, query(L, R, u->l), query(L, R, u->r));
	}
};
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t, kase = 0; cin >> t; while (t--){
		cout << "Case " << ++kase << ":\n";
		int n; cin >> n;
		int data[MAXN];
		for (int i = 0 ; i < n ; i++) cin >> data[i];
		SegmentTree *sol = new SegmentTree(data, n);
		char buf[10]; 
		bool stop = false;
		while (cin >> buf){
			if (buf[0] == 'E'){
				break;
			}
			int a, b; cin >> a >> b;
			switch(buf[0]){
				case 'A':
					sol->modify(a-1, a, b);
					break;
				case 'S':
					sol->modify(a-1, a, -b);
					break;
				case 'Q':
					cout << sol->query(a-1, b)->sum << '\n';
					break;
				case 'E':
					stop = true;
					break;
			}
		}
		delete sol;
	}
}
