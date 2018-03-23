#include <bits/stdc++.h>
using namespace std;
struct SplayTree{
	struct Node{
		Node *pa, *ch[2];
		int v, sz, minV;
		int add;
		bool rev;
		Node(int _v = 0){
			minV = v = _v;
			sz = 1;
			add = rev = 0;
		}
		inline void push(){

		}
		inline void pull(){

		}
	}*root;

};
int main(){

}
