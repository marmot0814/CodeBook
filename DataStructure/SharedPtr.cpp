#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct _ptrCntr{
	T v; int cnt;
	_ptrCntr(const T& _v = 0){
		cnt = 0; v = _v;
	}
};
template <typename T>
struct Sptr{
	_ptrCntr<T> *p;
	T *operator->(){return &p->v;}
	T &operator*(){return p->v;}
	operator _ptrCntr<T>*(){return p;}
	Sptr &operator = (const Sptr& t){
		if (p && !--p->cnt) delete p;
		(p = t.p) && ++p->cnt;
		return *this;
	}
	Sptr(_ptrCntr<T> *t = 0){ (p = t) && ++p->cnt;}
	Sptr(const Sptr &t){ (p = t.p) && ++p->cnt; }
	~Sptr(){ if (p && !--p->cnt) delete p; }
};
template <typename T>
inline Sptr<T> _new (const T& nd){
	return Sptr<T>(new _ptrCntr<T>(nd));
}
int main(){

}
