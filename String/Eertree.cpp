#include <bits/stdc++.h>
using namespace std;
const int SIGMA = 26;
inline int idx(char c){
	return c - 'a';
}
struct Eertree{
	struct Node{
		Node* n[SIGMA], f;
		int len;
		Node(int _len = 0) : f(NULL), len(_len){
			memset(n, 0, sizeof(n));
		}
	}*last, *rt;
	int n;
	vector<char> s;
	Eertree(char *input){
		s.clear(), s.PB(-1); n = 0;
		rt = new Node(0);
		rt->f = last = new Node(-1);
		for (int i = 0 ; input[i] ; i++) add(input[i]);
	}
	inline Node* getFail(Node *u){
		while (s[n - u->len - 1 ] != s[n])
			u = u->f;
		return u;
	}
	inline void add(char c){
		s.PB(c); n++;
		Node *u = getFail(last);
		if (!u->n[idx(c)]){
			
		}
	}
};
int main(){

}
