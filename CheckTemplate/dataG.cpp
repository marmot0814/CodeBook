#include <bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	int t = 2; cout << t << '\n';
	while (t--){
		int n = 1000; cout << n << '\n';
		for (int i = 0 ; i < n ; i++) cout << rand() % 100 << (i == n-1 ? '\n' : ' ');
		int q = 1000;
		char o[3][100] = {"Add", "Sub", "Query"};
		while (q--){
			int order = rand() % 3;
			cout << o[order] << ' ';
			int a = 0, b = 0;
			if (order == 0 || order == 1){
				a = rand() % n + 1;
				b = rand() % 30;
			}else{
				a = 0, b = 0;
				while (a == b){
					a = rand() % n + 1;
					b = rand() % n + 1;
					if (a > b) swap(a, b);
				}
			}
			cout << a << ' ' << b << '\n';
		}
		cout << "END\n";
	}
}
