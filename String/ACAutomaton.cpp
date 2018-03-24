#include <bits/stdc++.h>
using namespace std;
struct ACAutomaton{
	struct Node{
		Node *n[SIGMA], *f;
		int dp;
		Node(){
			memset(next, 0, sizeof(next));
			dp = 0; f = NULL;
		}
	}*r, *o, _mem[MAXN], *ptr;
	ACAutomaton(char **input, int n){
		ptr = _mem;
		o = new (ptr++) Node();
		r = new (ptr++) Node();
		for (int i = 0 ; i < n ; i++)
			buildTrie(input[i]);
		buildAC();
	}
	void buildTrie(
};
int main(){

}
