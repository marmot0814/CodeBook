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
 	operator _ptrCntr<T>*(){ return p; }
	Sptr& operator = (const Sptr& t){
		if (p && !--p->cnt) delete p;
		(p = t.p) && ++p->cnt; return *this;
	}
	Sptr(_ptrCntr<T> *t = NULL) : p(t) {p && ++p->cnt;}
	Sptr(const Sptr& t) : p(t.p) { p && ++p->cnt; }
	~Sptr() { if (p && !--p->cnt) delete p; }
};
template <typename T>
inline Sptr<T> _new(const T& u){
	return Sptr<T>(new _ptrCntr<T>(u));
}
// PersistentTreap
const int MAXK = 100;
struct PersistentTreap{
	struct Node{
		Sptr<Node> l, r;
		int sz; char c;
		bool rev;
		Node(char _c = 0) : l(NULL), r(NULL){
			c = _c, sz = 1;
			rev = false;
		}
	};
	Sptr<Node> rt[MAXK];
	int kCnt;
	PersistentTreap(){
		kCnt = 0;
	}
	inline int size(Sptr<Node> &u){
		return u ? u->sz : 0;
	}
	inline void pull(Sptr<Node> &u){
		if (!u) return ;
		push(u->l), push(u->r);
		u->sz = 1 + size(u->l) + size(u->r);

	}
	inline void push(Sptr<Node> &u){
		if (!u) return ;
		if (u->rev){
			swap(u->l, u->r);
			if (u->l) u->l = copy(u->l); u->l->rev ^= 1;
			if (u->r) u->r = copy(u->r); u->r->rev ^= 1;
			u->rev = false;
		}
	}
	Sptr<Node> copy(Sptr<Node> &u){
		return _new(*u);
	}
	Sptr<Node> merge(Sptr<Node> &T1, Sptr<Node> &T2){
		if (!T1 || !T2) return T1 ? T1 : T2;
		Sptr<Node> res;
		if (rand() % (size(T1) + size(T2)) < size(T1)){
			push(T1);
			res = copy(T1);
			res->r = merge(T1->r, T2);
		}else{
			push(T2);
			res = copy(T2);
			res->l = merge(T1, T2->l);
		}
		pull(res);
		return res;
	}
#define PNN pair<Sptr<Node>, Sptr<Node> >
#define MP make_pair
#define F first
#define S second
	PNN split(Sptr<Node> &T, int k){
		if (!T) return MP(Sptr<Node>(NULL), Sptr<Node>(NULL));
		push(T);
		Sptr<Node> res = copy(T);
		if (size(T->l) + 1 <= k){
			PNN tmp = split(res->r, k - 1 - size(res->l));
			pull(res);
			return MP(res, tmp.S);
		}else{
			PNN tmp = split(res->l, k);
			pull(res);
			return MP(tmp.F, res);
		}
	}
	void Print(){
		for (int i = 0 ; i <= kCnt ; i++){
			cout << "Treap " << i << ":\n";
			Print(rt[i]);
			cout << '\n';
		}
	}
	void Print(Sptr<Node> &u){
		if (!u) return ;
		Print(u->l);
		cout << u->c;
		Print(u->r);
	}
	void insert(char c, int k = -1){
		if (!~k) k = size(rt[kCnt]);
		Sptr<Node> u = _new(Node(c));
		rt[kCnt + 1] = merge(rt[kCnt], u);
		kCnt++;
	}
	void reverse(int a, int b){
		PNN tmp_1 = split(rt[kCnt], b);
		PNN tmp_2 = split(tmp_1.F, a-1);
		tmp_2.S->rev ^= 1;
		Sptr<Node> tmp = merge(tmp_2.F, tmp_2.S);
		rt[kCnt + 1] = merge(tmp, tmp_1.S);
		kCnt++;
	}
};
int main(){
	Sptr<PersistentTreap> sol = _new(PersistentTreap());
	sol->insert('V');
	sol->insert('E');
	sol->insert('d');
	sol->insert('4');
	sol->Print();
	sol->reverse(2, 4);
	sol->Print();
}
