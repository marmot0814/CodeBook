#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct _ptrCntr{
	T v; int cnt;
	_ptrCntr(const T& _v) : v(_v), cnt(0){}
};
template <typename T>
struct Sptr{
	_ptrCntr<T> *p;
	T* operator->(){ return &p->v; }
	T& operator* (){ return p->v; }
	operator _ptrCntr<T>*(){ return p;}
	Sptr& operator = (const Sptr& t){
		if (p && !--p->cnt) delete p;
		(p = t.p) && ++p->cnt;
		return *this;
	}
	Sptr(_ptrCntr<T> *t = NULL) : p(t) {
		p && ++p->cnt;
	}
	Sptr(const Sptr& t) : p(t.p) {p && ++p->cnt; }
	~Sptr() {
		if (p && !--p->cnt)
			delete p;
	}
};
template <typename T>
inline Sptr<T> _new(const T& u){
	return Sptr<T>(new _ptrCntr<T>(u));
}
const int MAXN = 150;
const int MAXK = 150;
struct PersistentSegmentTree{
	struct Node{
		Sptr<Node> l, r;
		int L, R;
		int cnt;
		Node(int _L, int _R) : l(NULL), r(NULL){
			L = _L, R = _R;
		}
		int len(){ return R - L; }
		int mid(){ return (R + L) >> 1; }
	};
	Sptr<Node> rt[MAXK];
	int n, kCnt;
	PersistentSegmentTree(int _n){
		n = _n;
		kCnt = 0;
		rt[0] = build(0, n);
	}
	Sptr<Node> copy(Sptr<Node> &u){
		return _new(*u);
	}
	Sptr<Node> build(int L, int R){
		Sptr<Node> u = _new(Node(L, R));
		if (u->len() == 1){
			u->cnt = 0;
			return u;
		}
		int M = u->mid();
		u->l = build(L, M);
		u->r = build(M, R);
		return pull(u);
	}
	Sptr<Node> pull(Sptr<Node> &u, Sptr<Node> &l, Sptr<Node> &r){
		if (!l || !r) return l ? l : r;
		u->cnt = l->cnt + r->cnt;
		return u;
	}
	Sptr<Node> pull(Sptr<Node> &u){
		return pull(u, u->l, u->r);
	}
	void modify(int pos, Sptr<Node> &u, Sptr<Node> &_u){
		if (u->R <= pos || pos + 1 <= u->L) return ;
		_u = copy(u);
		if (pos <= u->L && u->R <= pos + 1){
			_u->cnt++;
			return ;
		}
		int M = u->mid();
		modify(pos, u->l, _u->l);
		modify(pos, u->r, _u->r);
		pull(_u);
	}
	int query(Sptr<Node> &l, Sptr<Node> &r, int k){
		if (r->len() == 1) return r->L;
		if (r->l->cnt - l->l->cnt < k)
			return query(l->r, r->r, k - (r->l->cnt - l->l->cnt));
		else 
			return query(l->l, r->l, k);
	}
	void modify(int pos){
		modify(pos, rt[kCnt], rt[kCnt + 1]);
		kCnt++;
	}
	int query(int qL, int qR, int k){
		return query(rt[qL], rt[qR], k);
	}
	void Print(){
		for (int i = 0 ; i <= kCnt ; i++){
			cout << "Tree " << i << ":\n";
			Print(rt[i]);
			cout << '\n';
		}
	}
	void Print(Sptr<Node> &u){
		if (!u) return ;
		cout << u->L << '\t' << u->R << '\t' << u->cnt << '\n';
		Print(u->l);
		Print(u->r);
	}
};
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, q; cin >> n >> q;
	int arr[MAXN], arrSort[MAXN];
	for (int i = 0 ; i < n ; i++) {
		cin >> arr[i];
		arrSort[i] = arr[i];
	}
	sort(arrSort, arrSort + n);
	vector<int> target;
	target.push_back(arrSort[0]);
	for (int i = 1 ; i < n ; i++)
		if (arrSort[i] != arrSort[i-1])
			target.push_back(arrSort[i]);
	Sptr<PersistentSegmentTree> sol = _new(PersistentSegmentTree(target.size()));
	for (int i = 0 ; i < n ; i++)
		sol->modify(lower_bound(target.begin(), target.end(), arr[i]) - target.begin());
	while (q--){
		int a, b, k; cin >> a >> b >> k;
		a--;
		cout << target[sol->query(a, b, k)] << '\n';
	}

}
