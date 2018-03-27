#include <bits/stdc++.h>
using namespace std;
// ONE BASE!!
const int MAXN = 5e4 + 5;
struct BIT{
	int data[MAXN], n;
	BIT(int *arr, int _n){ n = _n;
		memset(data, 0, sizeof(data));
		for (int i = 1 ; i <= n ; i++)
			add(i, arr[i]);
	}
	int lowbit(int x) { return x & (-x); }
	int sum(int x){
		int res = 0;
		while (x > 0) res += data[x], x -= lowbit(x);
		return res;
	}
	void add(int x, int d){
		while (x <= n) data[x] += d, x += lowbit(x);
	}
};
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t, kase = 0; cin >> t; while (t--){
		cout << "Case " << ++kase << ":\n";
		int n; cin >> n;
		int arr[MAXN];
		for (int i = 1 ; i <= n ; i++) cin >> arr[i];
		BIT *sol = new BIT(arr, n);
		char op[10];
		while (cin >> op){
			int a, b;
			if (op[0] == 'E') break;
			if (op[0] == 'Q'){
				cin >> a >> b;
				cout << sol->sum(b) - sol->sum(a-1) << '\n';
			}
			if (op[0] == 'A'){
				cin >> a >> b;
				sol->add(a, b);
			}
			if (op[0] == 'S'){
				cin >> a >> b;
				sol->add(a, -b);
			}
		}
	}
}
