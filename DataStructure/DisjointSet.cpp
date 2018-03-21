#include <bits/stdc++.h>
using namespace std;
struct DisjointSet{
	int n;
	vector<int> pa;
	DisjointSet(int _n){
		n = _n;
		pa.resize(n + 1, -1);
	}
	int find(int p){
		return pa[p] < 0 ? p : pa[p] = find(pa[p]);
	}
	bool Union(int u, int v){
		int x = find(u), y = find(v);
		if (x != y){
			if (pa[x] < pa[y]) swap(x, y);
			pa[y] += pa[x], pa[x] = y;
		}
		return x != y;
	}
	void Print(){
		for (int i = 0 ; i < n ; i++)
			cout << pa[i] << (i == n-1 ? '\n' : ' ');
	}
};
int main(){
	DisjointSet *sol = new DisjointSet(10);
	sol->Print();
	while (1){
		int x = rand() % 10;
		int y = rand() % 10;
		cout << x << ' ' << y << '\n';
		sol->Union(x, y);
		sol->Print();
		int next;
		cin >>next;
	}
}
