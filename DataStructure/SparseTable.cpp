#include <bits/stdc++.h>
using namespace std;
#define PB push_back
struct SparseTable{
	vector<vector<int> > data;
	int (*op)(int a, int b);
	SparseTable(int *arr, int n, int (*_op)(int a, int b)){
		op = _op;
		int lgN = ceil(__lg(n));
		data.resize(lgN + 2);
		for (int i = 0 ; i < n ; i++) data[0].PB(arr[i]);
		for (int h = 1 ; h < lgN ; h++){
			int len = 1 << (h-1), i = 0;
			for (; i + len < n ; i++)
				data[h].PB(op(data[h-1][i], data[h-1][i+len]));
			if (!i) break;
			for (; i < n ; i++)
				data[h].PB(data[h-1][i]);
		}
	}
	int query(int l, int r){
		int h = __lg(r - l);
		int len = 1 << h;
		return op(data[h][l], data[h][r-len]);
	}
};
int getMin(int a, int b){
	return a < b ? a : b;
}
const int MAXN = 1000;
int main(){
	int arr[MAXN], n;
	cin >> n;
	for (int i = 0 ; i < n ; i++) cin >> arr[i];
	SparseTable *sol = new SparseTable(arr, n, getMin);
	int l, r;
	while (cin >> l >> r)
		cout << sol->query(l, r) << '\n';
	delete sol;
}
