
#include <bits/stdc++.h>
using namespace std;
// SmartPointer
template <typename T>
struct _ptrCntr{
	T v; int cnt;
	_ptrCntr(const T& _v = 0) : v(_v), cnt(0){}
};
template <typename T>
struct Sptr{
	_ptrCntr<T> *p;
	T* operator->(){ return &p->v; }
	T& operator*(){ return p->v; }
	operator _ptrCntr<T>*(){ return p;}
	Sptr& operator = (const Sptr& t){
		if (p && !--p->cnt) delete p;
		(p = t.p) && ++p->cnt; return *this;
	}
	Sptr(_ptrCntr<T> *t = NULL) : p(t){p && ++p->cnt;}
	Sptr(const Sptr &t) : p(t.p){p && ++p->cnt;}
	~Sptr(){ if (p && !--p->cnt) delete p;}
};
template <typename T>
inline Sptr<T> _new(const T& u){
	return Sptr<T>(new _ptrCntr<T>(u));
}
// PersistentSegmentTree
const int MAXN = 1e5 + 5;
const int lgN = __lg(MAXN) + 5;
const int MAXK = 100;
struct PersistentSegmentTree{
	struct Node{
		Sptr<Node> l, r;
		int L, R;
		// data
		// tag
		Node(int _L, int _R) : l(NULL), r(NULL){
			L = _L, R = _R;
			// data tag init
		}
		int len(){ return R - L; }
		int mid(){ return (R + L) >> 1; }
	};
	Sptr<Node> rt[MAXK];
	int *arr, n, kCnt;
	PersistentSegmentTree(int *_arr, int _n){
		arr = _arr, n = _n; kCnt = 0;
		rt[0] = build(0, n);
	}
	Sptr<Node> copy(Sptr<Node> &u){
		return _new(*u);
	}
	Sptr<Node> build(int L, int R){
		Sptr<Node> u = _new(Node(L, R));
		if (u->len() == 1){
			u->sum = arr[L];
			return u;
		}
		int M = u->mid();
		u->l = build(L, M);
		u->r = build(M, R);
		return pull(u);
	}
	Sptr<Node> pull(Sptr<Node> &u, Sptr<Node> &l, Sptr<Node> &r){
		if (!l || !r) return l ? l : r;
		push(l), push(r);
		// pull function
		return u;
	}
	void push(Sptr<Node> &u){
		if (!u) return ;
		// push function
	}
	Sptr<Node> pull(Sptr<Node> &u){
		return pull(u, u->l, u->r);
	}
	void modify(int mL, int mR, int v, Sptr<Node> &u, Sptr<Node> &_u){
		if (u->R <= mL || mR <= u->L) return ;
		_u = copy(u);
		if (mL <= u->L && u->R <= mR) {
			// tag (on copy node)
			return ;
		}
		push(u);
		int M = u->mid();
		modify(mL, mR, v, u->l, _u->l);
		modify(mL, mR, v, u->r, _u->r);
		pull(_u);
	}
	Sptr<Node> query(int qL, int qR, Sptr<Node> &u){
		if (u->R <= qL || qR <= u->L) return Sptr<Node>(NULL);
		if (qL <= u->L && u->R <= qR) return u;
		push(u); int M = u->mid();
		Sptr<Node> res = _new(Node(u->L, u->R));
		Sptr<Node> l = query(qL, qR, u->l);
		Sptr<Node> r = query(qL, qR, u->r);
		return pull(res, l, r);
	}
	void modify(int mL, int mR, int v){
		modify(mL, mR, v, rt[kCnt], rt[kCnt + 1]);
		kCnt++;
	}
	Sptr<Node> query(int qL, int qR, int k){
		return query(qL, qR, rt[k]);
	}
};
int main(){
	int arr[MAXN], n;
	cin >> n;
	for (int i = 0 ; i < n ; i++) cin >> arr[i];
	Sptr<PersistentSegmentTree> sol = _new(PersistentSegmentTree(arr, n));
	char op;
	while (cin >> op){
		int a, b, v;
		if (op == 'A'){
			cin >> a >> b >> v;
			sol->modify(a, b, v);
		}
		if (op == 'Q'){
			cin >> a >> b >> v;
			cout << sol->query(a, b, v)->sum << '\n';
		}
	}
	sol->Print();
}

