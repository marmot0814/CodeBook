#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int lgN = __lg(MAXN) + 5;
template <typename T>
class SegmentTree{
private:
	struct Node{
		Node *l, *r;
		int L, R;
		T* v;
		Node () {}
		Node (int _L, int _R, int _v){
			L = _L, R = _R;
			l = r = NULL;
			v = new T(_v);
		}
		~Node(){ delete v; }
	}*rt, buf[lgN << 2], *ptr;
	int n;
	Node* build(int L, int R){
		Node *u = new Node
	}
public:
	SegmentTree(int _n) : n(_n){
		rt = build(0, n);
	}
};
int main(){

}
