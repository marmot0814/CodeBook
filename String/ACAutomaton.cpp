#include <bits/stdc++.h>
using namespace std;
const int SIGMA = 26;
const int MAXLEN = 1e5;
struct ACAutomaton{
	struct Node{
		Node *n[SIGMA], *f;
		int dp;
		Node(){
			memset(n, 0, sizeof(n));
			dp = 0; f = NULL;
		}
	}*r, *o;
	ACAutomaton(int n){
		o = new Node();
		r = new Node();
		for (int i = 0 ; i < n ; i++){
			char input[MAXLEN]; cin >> input;
			buildTrie(input);
		}
		buildAC();
	}
	~ACAutomaton(){
		remove(r);
		delete o;
	}
	void remove(Node *u){
		if (!u) return ;
		for (int i = 0 ; i < SIGMA ; i++)
			remove(u->n[i]);
		delete u;
	}
	inline int idx(char c){
		// mapping function;
		return c - 'a';
	}
	void buildTrie(char *s){
		Node *u = r;
		for (int i = 0 ; s[i] ; i++){
			int c = idx(s[i]);
			if (!u->n[c])
				u->n[c] = new Node();
			u = u->n[c];
		}
		u->dp++;
	}
	void buildAC(){
		static queue<Node*> q;
		for (int i = 0 ; i < SIGMA ; i++)
			o->n[i] = r;
		r->f = o; q.push(r);
		while (q.size()){
			Node *u = q.front(); q.pop();
			for (int i = 0 ; i < SIGMA ; i++){
				if (!u->n[i]) continue;
				u->n[i]->f = trans(u->f, i);
				q.push(u->n[i]);
			}
			// u->dp += u->f->dp;
		}
	}
	Node* trans(Node *u, int c){
		while (!u->n[c]) u = u->f;
		return u->n[c];
	}
	int search(char *s){
		int ans = 0;
		Node *u = r;
		for (int i = 0 ; i < s[i] ; i++){
			u = trans(u, idx(s[i]));
			ans += u->dp;
		}
		return ans;
	}
	
};
int main(){

}
