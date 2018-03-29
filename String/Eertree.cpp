#include <bits/stdc++.h>
using namespace std;
#define PB push_back
const int SIGMA = 26;
inline int idx(char c){ return c - 'a'; }
struct Eertree{
	struct Node{
		Node *n[SIGMA], *f;
		int len;
		Node (int _len = 0){
			len = _len, f = NULL;
			memset(n, 0, sizeof(n));
		}
	}*last, *rt;
	vector<char> s;
	int n, maxLen, sz;
	Eertree(char *input){
		s.clear(), s.PB(-1); n = 0;
		rt = new Node(0); maxLen = -1;
		last = new Node(-1); sz = 0;
		rt->f = last; last->f = last;
		for (int i = 0 ; input[i] ; i++) add(input[i]);
	}
	inline Node* getFail(Node *u){
		while (s[n - u->len - 1] != s[n]) u = u->f;
		return u;
	}
	inline void add(char c){
		s.PB(c); n++;
		Node *u = getFail(last);
		if (!u->n[idx(c)]){
			Node *v = new Node(u->len + 2);
			maxLen = max(maxLen, v->len);
			sz++;
			v->f = getFail(u->f)->n[idx(c)];
			if (!v->f) v->f = rt;
			u->n[idx(c)] = v;
		}
		last = u->n[idx(c)];
	}
};
const int MAXLEN = 100;
int main(){
	char input[MAXLEN];
	while (cin >> input){
		Eertree *sol = new Eertree(input);
		cout << sol->maxLen << '\n';
		cout << sol->sz << '\n';
	}
}

