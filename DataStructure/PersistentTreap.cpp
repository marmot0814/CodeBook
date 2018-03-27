#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct _ptrCntr{
	T v; int c;
	_ptrCntr(const T& _v):v(_v){ c = 0;}
};
template <typename T>
struct Sptr{
	_ptrCntr<T> *p;
	T* operator->(){ return &p->v; }
	T& operator* (){ return  p->v; }
	operator _ptrCntr<T>*(){ return p; }
	Sptr& operator = (const Sptr<T>& t){
		if (p && !--p->c) delete p;
		(p = t.p) && ++p->c;
		return *this;
	}
	Sptr(_ptrCntr<T> *t = 0) : p(t){ p && ++p->c; }
	Sptr(const Sptr& t) : p(t.p){ p  && ++p->c; }
	~Sptr(){ if (p && !--p->c) delete p;}
};
template <typename T>
inline Sptr<T> _new(const T& u){
	return Sptr<T>(new _ptrCntr<T>(u));
}
#define PNN pair<Sptr<Node>, Sptr<Node> >
#define MP make_pair
#define F first
#define S second
const int MAXK = 5e4 + 5;
int d;
struct PersistentTreap{
	struct Node{
		Sptr<Node> l, r;
		int sz;
		// data
		// tag
		Node() : l(NULL), r(NULL){
			sz = 1;
		}
	};
	Sptr<Node> ver[MAXK];
	int verCnt;
	PersistentTreap(){ verCnt = 0; }
	inline int size(Sptr<Node> &u){
		return u ? u->sz : 0;
	}
	inline void push(Sptr<Node> &u){
		// push function
		// copy a new one and modify on it
	}
	inline Sptr<Node> pull(Sptr<Node> &u){
		u->sz = 1 + size(u->l) + size(u->r);
		// pull function
		return u;
	}
	inline Sptr<Node> copy(Sptr<Node> &u){
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
		return pull(res);
	}
	PNN split(Sptr<Node> &T, int k){
		if (!T) return MP(Sptr<Node>(NULL), Sptr<Node>(NULL));
		push(T);
		Sptr<Node> res = copy(T);
		if (size(T->l) < k){
			PNN tmp = split(T->r, k - 1 - size(T->l));
			res->r = tmp.F;
			return MP(pull(res), tmp.S);
		}else{
			PNN tmp = split(T->l, k);
			res->l = tmp.S;
			return MP(tmp.F, pull(res));
		}
	}
	/*	create a version  : verCnt++, ver[verCnt] = ver[verCnt - 1]
	 *	Treap operator
	 *	Query dont need to merge
	 */
};
int main(){
}
