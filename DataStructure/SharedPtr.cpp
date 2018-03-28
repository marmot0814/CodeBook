#include <bits/stdc++.h>
#define MP make_pair
#define F first
#define S second
using namespace std;
template <typename T>
struct Sptr{
	pair<T, int> *p;
	T *operator->(){return &p->F;}
	T &operator*(){return p->F;}
	operator pair<T, int>*(){return p;}
	Sptr &operator = (const Sptr& t){
		if (p && !--p->S) delete p;
		(p = t.p) && ++p->S;
		return *this;
	}
	Sptr(pair<T, int> *t = 0) : p(t){ p && ++p->S;}
	Sptr(const Sptr &t) : p(t.p) { p && ++p->S; }
	~Sptr(){ if (p && !--p->S) delete p; }
};
template <typename T>
inline Sptr<T> _new (const T& n){
	return Sptr<T>(new pair<T, int>(n, 0));
}
int main(){
	Sptr<int> a = _new(4);
	cout << a << ' ' << *a << '\n';
}
