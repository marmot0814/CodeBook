#include <bits/stdc++.h>
using namespace std;
const int SIGMA = 26;
inline int idx(char c){ return c - 'a'; }
struct Eertree{
	struct Node{
		Node *n[SIGMA], *f;
		int l;
		Node (int _l = 0) : f(NULL), l(_l){
			memset(n, 0, sizeof(n));
		}
	};
	Node *last;
	Eertree(){

	}
};
int main(){

}
