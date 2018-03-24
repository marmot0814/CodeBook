#include <bits/stdc++.h>
using namespace std;
const int SIGMA = 26;
const int MAXFINDLEN = 50 + 5;
struct ACAutomaton{
	struct Node{
		Node *n[SIGMA], *f;
		int dp; bool vis;
		Node(){
			memset(n, 0, sizeof(n));
			dp = 0; f = NULL; vis = false;
		}
	}*r, *o;
	ACAutomaton(char input[][MAXFINDLEN], int n){
		o = new Node();
		r = new Node();
		for (int i = 0 ; i < n ; i++)
			buildTrie(input[i]);
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
		}
	}
	Node* trans(Node *u, int c){
		while (!u->n[c]) u = u->f;
		return u->n[c];
	}
	int search(char *s){
		int ans = 0;
		Node *u = r;
		for (int i = 0 ; s[i] ; i++){
			u = trans(u, idx(s[i]));
			Node *t = u;
			while (t != r && !t->vis){
				ans += t->dp;
				t->vis = true;
				t = t->f;
			}
		}
		return ans;
	}
};
const int MAXN = 1e4 + 5;
const int MAXLEN = 1e6 + 5;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t; while (t--){
		int n; cin >> n;
		char input[MAXN][MAXFINDLEN];
		for (int i = 0 ; i < n ; i++)
			cin >> input[i];
		ACAutomaton *sol = new ACAutomaton(input, n);
		char target[MAXLEN]; cin >> target;
		cout << sol->search(target) << '\n';
		delete sol;
	}
}
